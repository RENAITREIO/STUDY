public class NBody {
    public static double readRadius(String file) {
        In in = new In(file);
        in.readInt();
		double radius = in.readDouble();
        return radius;
    }
    public static Planet[] readPlanets(String file) {
        In in = new In(file);
        int num = in.readInt();
        in.readDouble();
        Planet[] allPlanets = new Planet[num];
        for (int i = 0; i < num; i++) {
            allPlanets[i] = new Planet(in.readDouble(), in.readDouble(), in.readDouble(), in.readDouble(), in.readDouble(), in.readString());
        }
        return allPlanets;
    }

    public static void main(String[] args) {
        if (args.length != 3) {
            return;
        }
        double T = Double.parseDouble(args[0]);
        double dt = Double.parseDouble(args[1]);
        String filename = args[2];
        double radius = readRadius(filename);
        Planet[] allPlanets = readPlanets(filename);

        StdDraw.setScale(-radius, radius);
        StdDraw.clear();
        StdDraw.picture(0, 0, "images/starfield.jpg");
        for (Planet p: allPlanets) {
            p.draw();
        }
        StdDraw.show();
        StdAudio.loop("audio/2001.mid");
        StdDraw.enableDoubleBuffering();
        double time = 0;
        while (time < T) {
            double[] xForces = new double[allPlanets.length];
            double[] yForces = new double[allPlanets.length];
            for (int i = 0; i < allPlanets.length; i++) {
                xForces[i] = allPlanets[i].calcNetForceExertedByX(allPlanets);
                yForces[i] = allPlanets[i].calcNetForceExertedByY(allPlanets);
            }
            for (int i = 0; i < allPlanets.length; i++) {
                allPlanets[i].update(dt, xForces[i], yForces[i]);
            }
            StdDraw.picture(0, 0, "images/starfield.jpg");
            for (Planet p: allPlanets) {
                p.draw();
            }
            StdDraw.show();
            StdDraw.pause(10);
            time += dt;
        }
        System.out.printf("%d\n", allPlanets.length);
        System.out.printf("%.2e\n", radius);
        for (int i = 0; i < allPlanets.length; i++) {
            System.out.printf("%11.4e %11.4e %11.4e %11.4e %11.4e %12s\n",
                        allPlanets[i].xxPos, allPlanets[i].yyPos, allPlanets[i].xxVel,
                        allPlanets[i].yyVel, allPlanets[i].mass, allPlanets[i].imgFileName);   
        }
    }
}