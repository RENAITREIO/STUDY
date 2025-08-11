#include "Plotter.h"
#include "strlib.h"
using namespace std;
// void drawLine(double x0, double y0, double x1, double y1, PenStyle info);
// struct PenStyle {
//     double width;
//     std::string color;
// };

void plotterInit();
void penDown();
void penUp();
void penColor(string color);
void penWidth(double width);

void moveAbs(double x, double y);
void moveRel(double dx, double dy);

double point_x;
double point_y;
PenStyle info;
bool penState;

void runPlotterScript(istream& input) {
    plotterInit();
    for (string line; getline(input, line); ) {
        Vector<string> arg = stringSplit(line, " ");
        arg[0] = toLowerCase(arg[0]);
        if (arg[0] == "pendown") {
            penDown();
        } else if (arg[0] == "penup") {
            penUp();
        } else if (arg[0] == "moveabs") {
            double x = stringToReal(arg[1]);
            double y = stringToReal(arg[2]);
            moveAbs(x, y);
        } else if (arg[0] == "moverel") {
            double dx = stringToReal(arg[1]);
            double dy = stringToReal(arg[2]);
            moveRel(dx, dy);
        } else if (arg[0] == "pencolor") {
            penColor(arg[1]);
        } else if (arg[0] == "penwidth") {
            double color = stringToReal(arg[1]);
            penWidth(color);
        } else {
            error("Invalid command.");
        }
    }
}

void plotterInit() {
    point_x = 0;
    point_y = 0;
    penColor("black");
    penWidth(1);
    penUp();
}

void penDown() {
    penState = 1;
}

void penUp() {
    penState = 0;
}

void moveAbs(double x, double y) {
    if (penState == 1) {
        drawLine(point_x, point_y, x, y, info);
    }
    point_x = x;
    point_y = y;
}

void moveRel(double dx, double dy) {
        moveAbs(point_x + dx, point_y + dy);
}

void penColor(string color) {
    info.color = color;
}

void penWidth(double width) {
    info.width = width;
}

