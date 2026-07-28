import edu.princeton.cs.algs4.Picture;

public class SeamCarver {
    private Picture pic;

    public SeamCarver(Picture picture) {
        this.pic = new Picture(picture.width(), picture.height());
        for (int i = 0; i < width(); i++) {
            for (int j = 0; j < height(); j++) {
                pic.set(i, j, picture.get(i, j));
            }
        }
    }

    // current picture
    public Picture picture() {
        Picture res = new Picture(pic.width(), pic.height());
        for (int i = 0; i < width(); i++) {
            for (int j = 0; j < height(); j++) {
                res.set(i, j, pic.get(i, j));
            }
        }
        return res;
    }

    // width of current picture
    public int width() {
        return this.pic.width();
    }

    // height of current picture
    public int height() {
        return this.pic.height();
    }

    // energy of pixel at column x and row y
    public double energy(int x, int y) {
        if (x < 0 || x >= width() || y < 0 || y >= height()) {
            throw new java.lang.IndexOutOfBoundsException();
        }
        return calEX(x, y) + calEY(x, y);
    }

    private double calEX(int x, int y) {
        int rgb1 = pic.get((x - 1 + width()) % width(), y).getRGB();
        int rgb2 = pic.get((x + 1) % width(), y).getRGB();
        return Math.pow(getRed(rgb1) - getRed(rgb2), 2)
                + Math.pow(getGreen(rgb1) - getGreen(rgb2), 2)
                + Math.pow(getBlue(rgb1) - getBlue(rgb2), 2);
    }

    private double calEY(int x, int y) {
        int rgb1 = pic.get(x, (y - 1 + height()) % height()).getRGB();
        int rgb2 = pic.get(x, (y + 1) % height()).getRGB();
        return Math.pow(getRed(rgb1) - getRed(rgb2), 2)
                + Math.pow(getGreen(rgb1) - getGreen(rgb2), 2)
                + Math.pow(getBlue(rgb1) - getBlue(rgb2), 2);
    }

    private int getRed(int rgb) {
        return rgb >> 16 & 255;
    }

    private int getGreen(int rgb) {
        return rgb >> 8 & 255;
    }

    private int getBlue(int rgb) {
        return rgb >> 0 & 255;
    }

    // sequence of indices for horizontal seam
    public int[] findHorizontalSeam() {
        reversePic();
        int[] result = findVerticalSeam();
        reversePic();
        return result;
    }

    private void reversePic() {
        Picture reversed = new Picture(pic.height(), pic.width());

        for (int i = 0; i < width(); i++) {
            for (int j = 0; j < height(); j++) {
                reversed.set(j, i, pic.get(i, j));
            }
        }
        pic = reversed;
    }

    // sequence of indices for vertical seam
    public int[] findVerticalSeam() {
        double[][] energyArr = getEnergyArr();
        int[] previous = new int[width() * height()];

        for (int j = 1; j < height(); j++) {
            for (int i = 0; i < width(); i++) {
                if (i - 1 < 0 && i + 1 > width() - 1) {
                    energyArr[i][j] += energyArr[i][j - 1];
                    previous[xyToIdx(i, j)] = xyToIdx(i, j - 1);
                } else if (i - 1 < 0) {
                    double energy1 = energyArr[i][j] + energyArr[i][j - 1];
                    double energy2 = energyArr[i][j] + energyArr[i + 1][j - 1];
                    if (energy1 > energy2) {
                        energyArr[i][j] = energy2;
                        previous[xyToIdx(i, j)] = xyToIdx(i + 1, j - 1);
                    } else {
                        energyArr[i][j] = energy1;
                        previous[xyToIdx(i, j)] = xyToIdx(i, j - 1);
                    }
                } else if (i + 1 > width() - 1) {
                    double energy1 = energyArr[i][j] + energyArr[i - 1][j - 1];
                    double energy2 = energyArr[i][j] + energyArr[i][j - 1];
                    if (energy1 > energy2) {
                        energyArr[i][j] = energy2;
                        previous[xyToIdx(i, j)] = xyToIdx(i, j - 1);
                    } else {
                        energyArr[i][j] = energy1;
                        previous[xyToIdx(i, j)] = xyToIdx(i - 1, j - 1);
                    }
                } else {
                    double energy1 = energyArr[i][j] + energyArr[i - 1][j - 1];
                    double energy2 = energyArr[i][j] + energyArr[i][j - 1];
                    double energy3 = energyArr[i][j] + energyArr[i + 1][j - 1];
                    double minimum = Math.min(Math.min(energy1, energy2), energy3);
                    energyArr[i][j] = minimum;
                    if (minimum == energy1) {
                        previous[xyToIdx(i, j)] = xyToIdx(i - 1, j - 1);
                    } else if (minimum == energy2) {
                        previous[xyToIdx(i, j)] = xyToIdx(i, j - 1);
                    } else {
                        previous[xyToIdx(i, j)] = xyToIdx(i + 1, j - 1);
                    }
                }
            }
        }

        int idx = 0;
        double minEnergy = Double.MAX_VALUE;
        for (int i = 0; i < width(); i++) {
            double val = energyArr[i][height() - 1];
            if (val < minEnergy) {
                minEnergy = val;
                idx = i;
            }
        }

        int[] result = new int[height()];
        for (int i = height() - 1; i >= 0; i--) {
            result[i] = idxToX(idx);
            idx = idxToX(previous[xyToIdx(idx, i)]);
        }
        return result;
    }

    private int xyToIdx(int x, int y) {
        return y * width() + x;
    }

    private int idxToX(int idx) {
        return idx % width();
    }

    private double[][] getEnergyArr() {
        double[][] newArr = new double[width()][height()];
        for (int i = 0; i < width(); i++) {
            for (int j = 0; j < height(); j++) {
                newArr[i][j] = energy(i, j);
            }
        }
        return newArr;
    }

    // remove horizontal seam from picture
    public void removeHorizontalSeam(int[] seam) {
        for (int i = 0; i < width() - 1; i++) {
            if (Math.abs(seam[i] - seam[i + 1]) > 1) {
                throw new java.lang.IllegalArgumentException();
            }
        }
        SeamRemover.removeHorizontalSeam(this.pic, seam);
    }

    // remove vertical seam from picture
    public void removeVerticalSeam(int[] seam) {
        for (int i = 0; i < height() - 1; i++) {
            if (Math.abs(seam[i] - seam[i + 1]) > 1) {
                throw new java.lang.IllegalArgumentException();
            }
        }
        SeamRemover.removeVerticalSeam(this.pic, seam);
    }
}
