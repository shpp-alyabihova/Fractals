#include <simpio.h>
#include "console.h"
#include "math.h"
#include "gwindow.h"
#include <string>

using namespace std;


const int NUM_ITERATION = 500;

const double DISTANCE_FROM_ORIGIN = 2;

const double WINDOW_WIDTH = 800;

const double WINDOW_HEIGHT = 600;


//converts values of r, g, b into a color with name in the form "#rrggbb", where each of the rr, gg, and bb values are two-digit hexadecimal numbers
string getColor(double r, double g, double b);

// converts integer from decimal to hexadecimal
string convertToHex(int number);

bool isPointInWindow(GWindow & gw, double, double);

//bilds the Mandelbrot set
int main() {
    GWindow gw(WINDOW_WIDTH, WINDOW_HEIGHT);

    for(int i = 0; i < WINDOW_HEIGHT; ++i){
        for(int j = 0; j < WINDOW_WIDTH; ++j){

             //sets the coordinates of each point of the window in the rectangular coordinate system
            double coordR = j - gw.getWidth()/2;
            double coordI = gw.getHeight()/2 - i;
            int num = 0;
            double x = 0;
            double y = 0;
            while(num <= NUM_ITERATION){
                double x_i = x; // remember the value of x on this iteration to calculate y

                //divide by 180 to get the polar coordinates
                x = x*x - y*y + coordR/180;
                y = 2*x_i*y + coordI/180;

                if(sqrt(x*x + y*y) >= 2){ // checks the point for belonging to the Mandelbrot set
                    break;
                }
                ++num;
            }


            // sets the r, g, b components of color for each point according to the number of iterations
            // for large values of the number of iterations the r, g, b components will match the white colol, it will be the Mandelbrot set
            //0.1, 0.2, 0.3, 0.03 are arbitrary constants to get r, g, b components for specific color
            double r = 0.1 + num * 0.03 * 0.2;
            double g = 0.2 + num * 0.03 * 0.3;
            double b = 0.3 + num * 0.03 * 0.1;

            //for values of components which is greater than one leads to one
            (r > 1) ?  r = 1 : r = r;
            (g > 1) ? g = 1 : g = g;
            (b > 1) ? b = 1 : b = b;

            string color = getColor(r, g, b);
            gw.setColor(color);


            //sets the coordinates of the point in the coordinates window
            x = gw.getWidth()/2 + coordR;
            y = gw.getHeight()/2 - coordI;
            gw.fillOval(x, y, 1, 1);
        }
    }
    return 0;
}


string getColor(double r, double g, double b){
    string red = convertToHex(r*255);
    string green = convertToHex(g*255);
    string blue = convertToHex(b*255);
    return "#" + red + green + blue;
}


string convertToHex(int number){
    string numHex = "0123456789ABCDEF";
    string numToHex = "";
    while(number/16 != 0){
        numToHex = numHex[number%16] + numToHex;
        number = number/16;
    }
    numToHex = numHex[number%16] + numToHex;
    if(numToHex.length() < 2){
        numToHex = "0" + numToHex;
    }
    return numToHex;
}


bool isPointInWindow(GWindow & gw, double coordX, double coordY){
    if((coordX >= gw.getWidth()) || (coordX <= 0) || (coordY >= gw.getHeight()) || (coordY <= 0)){
        return false;
    }
    return true;
}



