#include <simpio.h>
#include "console.h"
#include "math.h"
#include "gwindow.h"
using namespace std;


const int RECURSION_DEPTH = 12;

const double WINDOW_WIDTH = 1000;

const double WINDOW_HEIGHT = 600;

// length of the element of the order 0
const double LENGTH = WINDOW_HEIGHT/5;

// the angle is measured in degrees counterclockwise from the axis X of the order 0
const double ANGLE = 90;

// deviation from the gotten angle for the next orders
const double THETA = 35;// must be < 90 (45 for classic Pythagorean tree)

const double PI = 3.14159;

//conversion of the angle from degrees to radians
const double THETA_RADIAN = (THETA * PI)/180;


/*
 * @param GWindow &gw takes a reference of the window
 * @param GPoint endPoint1 and endPoint2 takes the end point of the lines
 * @param double length takes a length of element of the privious order
 * @param double theta takes the angle of the privious order
 * @param int depth takes a value of recursion depth
 */
void buildPythagoreanTree(GWindow &gw, GPoint endPoint1, GPoint endPoint2, double length, double theta, int depth);

bool isPointInWindow(GWindow & gw, GPoint p);

//bilds the element of the order 0 and then calls function for building other elemens according to the depth of recursion
int main() {
    GWindow gw(WINDOW_WIDTH, WINDOW_HEIGHT);
    gw.setColor("Black");
    gw.fillRect(0, 0, gw.getWidth(), gw.getHeight());
    gw.setColor("CYAN");
    gw.drawLine(gw.getWidth()/2 - LENGTH/2, gw.getHeight(), gw.getWidth()/2 + LENGTH/2, gw.getHeight());
    GPoint start1(gw.getWidth()/2 - LENGTH/2, gw.getHeight());
    GPoint endPoint1 = gw.drawPolarLine(start1, LENGTH, ANGLE);
    GPoint start2(gw.getWidth()/2 + LENGTH/2, gw.getHeight());
    GPoint endPoint2 = gw.drawPolarLine(start2, LENGTH, ANGLE);
    gw.drawLine(endPoint1, endPoint2);
    buildPythagoreanTree(gw, endPoint1, endPoint2, LENGTH, ANGLE, RECURSION_DEPTH);
    return 0;
}


//buids two lines from each of two gotten vertex and calls itself recursively until the depth of recursion becomes zero
void buildPythagoreanTree(GWindow &gw, GPoint endPoint1, GPoint endPoint2, double length, double theta, int depth){
        double theta1 = theta - (ANGLE - THETA);
        double theta2 = theta + THETA;


        double length1 = length * cos(THETA_RADIAN);
        double length2 = length * sin(THETA_RADIAN);

        GPoint next1_2 = gw.drawPolarLine(endPoint1, length1 + length2, theta1);
        GPoint next2_2 = gw.drawPolarLine(endPoint2, length2, theta1);
        gw.drawLine(next1_2, next2_2);
        GPoint next1_1 = gw.drawPolarLine(endPoint1, length1, theta2);
        GPoint next2_1 = gw.drawPolarLine(endPoint2, length2 + length1, theta2);
        gw.drawLine(next1_1, next2_1);

        --depth;

        if(depth == 0){
            return;
        }
        else{
            if((isPointInWindow(gw, next1_2)) && (isPointInWindow(gw, next2_2))){
                buildPythagoreanTree(gw, next1_2, next2_2, length2, theta1, depth);
            }
            if((isPointInWindow(gw, next1_1)) && (isPointInWindow(gw, next2_1))){
                buildPythagoreanTree(gw, next1_1, next2_1, length1, theta2, depth);
            }
    }
}


bool isPointInWindow(GWindow & gw, GPoint p){
    double coordX = p.getX();
    double coordY = p.getY();
    if((coordX >= gw.getWidth()) || (coordX <= 0) || (coordY >= gw.getHeight()) || (coordY <= 0)){
        return false;
    }
    return true;
}


