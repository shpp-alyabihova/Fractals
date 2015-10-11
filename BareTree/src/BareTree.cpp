#include "console.h"
#include "math.h"
#include "gwindow.h"
using namespace std;


const int RECURSION_DEPTH = 15;

const double WINDOW_WIDTH = 1000;

const double WINDOW_HEIGHT = 600;

// length of the element of the order 0
const double LENGTH = WINDOW_HEIGHT/5;

// the angle is measured in degrees counterclockwise from the axis X of the order 0
const double ANGLE = 90;

// deviation from the gotten angle for the next orders
const double THETA = 45;

// coofficient of the deviation from the gotten angle for getting windswept Pythagorean tree
const double DELTA_THETA = 0.6; // 0 for classic Pythagorean tree


/*
 * @param GWindow &gw takes a reference of the window
 * @param GPoint finish takes the end point of the line
 * @param double length takes a length of element of the privious order
 * @param double theta takes the angle of the privious order
 * @param int depth takes a value of recursion depth
 */
void buildPythagoreanTree(GWindow &gw, GPoint finish, double length, double theta, int depth);

bool isPointInWindow(GWindow & gw, GPoint p);

//bilds the element of the order 0 and then calls function for building other elemens according to the depth of recursion
int main() {
    GWindow gw(WINDOW_WIDTH, WINDOW_HEIGHT);
    gw.setColor("Black");
    gw.fillRect(0, 0, gw.getWidth(), gw.getHeight());
    gw.setColor("CYAN");
    GPoint start(gw.getWidth()/2, gw.getHeight());
    GPoint finish = gw.drawPolarLine(start, LENGTH, ANGLE);
    buildPythagoreanTree(gw, finish, LENGTH, ANGLE, RECURSION_DEPTH);
    return 0;
}


//buids two lines from gotten vertex and calls itself recursively until the depth of recursion becomes zero
void buildPythagoreanTree(GWindow &gw, GPoint finish, double length, double theta, int depth){
        double theta1 = theta - THETA;
        double theta2 = theta + THETA * (1 - DELTA_THETA);
        length = sqrt(pow(length, 2)/2);
        GPoint next1 = gw.drawPolarLine(finish, length, theta1);
        GPoint next2 = gw.drawPolarLine(finish, length, theta2);
        --depth;
        if(depth == 0){
            return;
        }
        else{
            if(isPointInWindow(gw, next1)){
                buildPythagoreanTree(gw, next1, length, theta1, depth);
            }
            if(isPointInWindow(gw, next2)){
                buildPythagoreanTree(gw, next2, length, theta2, depth);
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
