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
#include <cmath>
#include <iostream>
#include <stdio.h>

#include "../CAMgraphics.h"
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

    CAMgraphics camGraphics;
    
    camGraphics.open("PlotSample");                 // open file graph.ps for output
    camGraphics.clearMultiPageFlag();               // suppress indexing of separate pages output since
                                                    // a single plot.

    camGraphics.setAxisRange(-3.0,3.0,-2.0,2.0);    // set plotting ranges
    camGraphics.title("Plot of function sin(x*x)"); // label the plot
    camGraphics.labelX(" X ");
    camGraphics.labelY(" Y ");

    camGraphics.setLineWidth(0.004);
    camGraphics.plot(x,y,n);                       // do the plotting
    camGraphics.frame();                           // "frame" the plot

    camGraphics.close();                           // close

    delete [] x;                         // clean up
    delete [] y;

    std::cout << "   Program Complete "    << std::endl << std::endl;
    return 0;
}
 
