import java.util.HashMap;
import java.util.Map;

/**
 * This class provides all code necessary to take a query box and produce
 * a query result. The getMapRaster method must return a Map containing all
 * seven of the required fields, otherwise the front end code will probably
 * not draw the output correctly.
 */
public class Rasterer {
    private final double STDLONDPP;

    public Rasterer() {
        STDLONDPP = (MapServer.ROOT_LRLON - MapServer.ROOT_ULLON) / MapServer.TILE_SIZE;
    }

    /**
     * Takes a user query and finds the grid of images that best matches the query. These
     * images will be combined into one big image (rastered) by the front end. <br>
     *
     *     The grid of images must obey the following properties, where image in the
     *     grid is referred to as a "tile".
     *     <ul>
     *         <li>The tiles collected must cover the most longitudinal distance per pixel
     *         (LonDPP) possible, while still covering less than or equal to the amount of
     *         longitudinal distance per pixel in the query box for the user viewport size. </li>
     *         <li>Contains all tiles that intersect the query bounding box that fulfill the
     *         above condition.</li>
     *         <li>The tiles must be arranged in-order to reconstruct the full image.</li>
     *     </ul>
     *
     * @param params Map of the HTTP GET request's query parameters - the query box and
     *               the user viewport width and height.
     *
     * @return A map of results for the front end as specified: <br>
     * "render_grid"   : String[][], the files to display. <br>
     * "raster_ul_lon" : Number, the bounding upper left longitude of the rastered image. <br>
     * "raster_ul_lat" : Number, the bounding upper left latitude of the rastered image. <br>
     * "raster_lr_lon" : Number, the bounding lower right longitude of the rastered image. <br>
     * "raster_lr_lat" : Number, the bounding lower right latitude of the rastered image. <br>
     * "depth"         : Number, the depth of the nodes of the rastered image <br>
     * "query_success" : Boolean, whether the query was able to successfully complete; don't
     *                    forget to set this to true on success! <br>
     */
    public Map<String, Object> getMapRaster(Map<String, Double> params) {
        Map<String, Object> results = new HashMap<>();

        if (!isLocationValid(params)) {
            results.put("query_success", false);
            return results;
        }

        int mapN = chooseMapN(params);
        int size = (int) Math.pow(2, mapN);
        double minimumLon = (MapServer.ROOT_LRLON - MapServer.ROOT_ULLON) / size;
        double minimumLat = (MapServer.ROOT_ULLAT - MapServer.ROOT_LRLAT) / size;

        int left = calLocation(MapServer.ROOT_ULLON, params.get("ullon"),
                size, minimumLon, true);
        int right = calLocation(MapServer.ROOT_ULLON, params.get("lrlon"),
                size, minimumLon, false);
        // for easier calculation
        int top = size - 1 - calLocation(MapServer.ROOT_LRLAT, params.get("ullat"),
                size, minimumLat, false);
        int bottom = size - 1 - calLocation(MapServer.ROOT_LRLAT, params.get("lrlat"),
                size, minimumLat, true);

        int xSize = right - left + 1;
        int ySize = bottom - top + 1;
        String[][] files = new String[ySize][xSize];
        for (int i = 0; i < ySize; i++) {
            for (int j = 0; j < xSize; j++) {
                files[i][j] = "d" + mapN + "_x" + (left + j) + "_y" + (top + i) + ".png";
            }
        }

        // for easier calculation
        top = size - 1 - top;
        bottom = size - 1 - bottom;

        results.put("render_grid", files);
        results.put("raster_ul_lon", MapServer.ROOT_ULLON + left * minimumLon);
        results.put("raster_ul_lat", MapServer.ROOT_LRLAT + (top + 1) * minimumLat);
        results.put("raster_lr_lon", MapServer.ROOT_ULLON + (right + 1) * minimumLon);
        results.put("raster_lr_lat", MapServer.ROOT_LRLAT + bottom * minimumLat);
        results.put("depth", mapN);
        results.put("query_success", true);

        // test
        System.out.println(params);
        System.out.println(results);
        return results;
    }


    private boolean isLocationValid(Map<String, Double> params) {
        double ullon = params.get("ullon");
        double lrlon = params.get("lrlon");
        double ullat = params.get("ullat");
        double lrlat = params.get("lrlat");

        boolean isReverse = ullon > lrlon || ullat < lrlat;
        boolean isOutOfBounds = ullon > MapServer.ROOT_LRLON || ullat < MapServer.ROOT_LRLAT
                || lrlon < MapServer.ROOT_ULLON || lrlat > MapServer.ROOT_ULLAT;

        return !(isReverse || isOutOfBounds);
    }

    private int chooseMapN(Map<String, Double> params) {
        double pLonDPP = (params.get("lrlon") - params.get("ullon")) / params.get("w");
        double properLonDPP = this.STDLONDPP;
        int n = 0;
        while (n < 7) {
            if (properLonDPP <= pLonDPP) {
                break;
            }
            properLonDPP /= 2;
            n++;
        }
        return n;
    }

    private int calLocation(double minimum, double target, int size,
                            double miniDistance, boolean chooseBigger) {
        double location = minimum;
        int n;
        for (n = 0; n < size - 1; n++) {
            location += miniDistance;
            if (chooseBigger) {
                if (target < location) {
                    break;
                }
            } else {
                if (target <= location) {
                    break;
                }
            }
        }
        return n;
    }

}
