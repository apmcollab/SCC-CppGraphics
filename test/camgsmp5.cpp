//
//######################################################################
//            CAMgraphics Sample Program  #5
//
// Chris Andersion (C) UCLA 1996                                10/4/96
//                                                              04/04/07
//######################################################################
//
/*
  	Creation of a surface plot
*/
#include "camgraph.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
using namespace std;
//
// Target Function 
//
double f(double x,double y)
{
return (3*(1-x)*(1-x)*(exp(-x*x - (y+1)*(y+1)))
          -10*(x/5 - x*x*x - y*y*y*y*y)*(exp(-x*x - y*y))
          -(1/3.0)*(exp(-(x+1)*(x+1) - y*y)));

};

int main()
{
    double a  = -3.0;                     // create data for surface plot
    double b  =  3.0;
    double c  = -3.0;
    double d =   3.0;

    long   n  =  20;

    double hx  = (b-a)/double(n-1);
    double hy  = (d-c)/double(n-1);

    double* x = new double[n];
    double* y = new double[n];

    double* z = new double[n*n];

    int i; int j;
    for(i=0; i < n; i++)
    {
    x[i]    = a + double(i)*hx;
    y[i]    = c + double(i)*hy;
    }

    for(i=0; i < n; i++)
    {
    for(j=0; j < n; j++)
    {
    z[i + n*j] = f(x[i],y[j]);          // fill 2d array; do my own
                                        // indexing because I want a
                                        // a variable sized array
    }}

    CAMgraphics::open("graph.ps");             // Open a file for output

    CAMgraphics::title("Sample Surface Plot"); // label the plot

    CAMgraphics::surface(z,n,n);                // create the contour plot
    CAMgraphics::frame();                       // "frame" the plot

    CAMgraphics::close();                       // close

    delete [] x;                         // clean up
    delete [] y;
    delete [] z;

    cout << "   Program Complete "    << endl << endl;
	return 0;
}
 
