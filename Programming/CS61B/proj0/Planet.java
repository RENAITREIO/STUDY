public class Planet {
    private static final double G = 6.67e-11;
    public double xxPos;
    public double yyPos;
    public double xxVel;
    public double yyVel;
    public double mass;
    public String imgFileName;

    public Planet(double xP, double yP, double xV,double yV, double m, String img) {
        xxPos = xP;
        yyPos = yP;
        xxVel = xV;
        yyVel = yV;
        mass = m;
        imgFileName = img;
    }
    public Planet(Planet p) {
        xxPos = p.xxPos;
        yyPos = p.yyPos;
        xxVel = p.xxVel;
        yyVel = p.yyVel;
        mass = p.mass;
        imgFileName = p.imgFileName;
    }

    public double calcDistance(Planet p) {
        double xD = this.xxPos - p.xxPos;
        double yD = this.yyPos - p.yyPos;
        return Math.sqrt(xD * xD + yD * yD);
    }
    public double calcForceExertedBy(Planet p) {
        double distance = this.calcDistance(p);
        return G * this.mass * p.mass / (distance * distance);
    }
    public double calcForceExertedByX(Planet p) {
        double dx = p.xxPos - this.xxPos;
        return calcForceExertedBy(p) * dx / calcDistance(p);
    }
    public double calcForceExertedByY(Planet p) {
        double dy = p.yyPos - this.yyPos;
        return calcForceExertedBy(p) * dy / calcDistance(p);
    }
    public double calcNetForceExertedByX(Planet[] allPlanets) {
        double res = 0;
        for (Planet p: allPlanets) {
            if (this.equals(p) == false) {
                res += calcForceExertedByX(p);
            }
        }
        return res;
    }
    public double calcNetForceExertedByY(Planet[] allPlanets) {
        double res = 0;
        for (Planet p: allPlanets) {
            if (this.equals(p) == false) {
                res += calcForceExertedByY(p);
            }
        }
        return res;
    }
    public void update(double dt, double fX, double fY) {
        double aX = fX / this.mass;
        double aY = fY / this.mass;
        this.xxVel += dt * aX;
        this.yyVel += dt * aY;
        this.xxPos += dt * this.xxVel;
        this.yyPos += dt * this.yyVel;
    }
    public void draw() {
        StdDraw.picture(this.xxPos, this.yyPos, "images/" + this.imgFileName);
    }
}