//
//######################################################################
//            CAMgraphics Sample Program  #1
//
// Chris Andersion (C) UCLA 1996                                1/7/97
//                                                            04/04/07
//######################################################################
//
/*
	Plots the function sin(x*x) over the interval [-3,3]
*/
#include "camgraph.h"
#include <math.h>
#include <iostream>
using namespace std;
#include <stdio.h>
//
// Function to be plotted
//
double f(double x){ return sin(x*x);};

int main()
{
    double a  = -3.0;                     // create data for line plot
    double b  =  3.0;
    long   n  =  50;                     
    double h  = (b-a)/double(n-1);

    double* x = new double[n];
    double* y = new double[n];

    int i;
    for(i=0; i < n; i++)
    {
    x[i] = a + double(i)*h;
    y[i] = f(x[i]);
    }

    CAMgraphics::open("graph.ps");                   // open file graph.ps for output

    CAMgraphics::setAxisRange(-3.0,3.0,-2.0,2.0);    // set plotting ranges
    CAMgraphics::title("Plot of function sin(x*x)"); // label the plot
    CAMgraphics::labelX(" X ");
    CAMgraphics::labelY(" Y ");

    CAMgraphics::plot(x,y,n);                       // do the plotting
    CAMgraphics::frame();                           // "frame" the plot

    CAMgraphics::close();                           // close

    delete [] x;                         // clean up
    delete [] y;

    cout << "   Program Complete "    << endl << endl;
    return 0;
}
 
