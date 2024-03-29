//
//######################################################################
//            CAMgraphicsProcess Sample Program  #1
//
// Chris Andersion (C) UCLA 1996                                1/7/97
//                                                              04/05/07
//######################################################################
//
/*
	Plots the function sin(x*x) over the interval [-3,3]
*/
#include "gprocess.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
using namespace std;

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

    CAMgraphicsProcess  Gprocess;                // declare a graphics process
    CAMpostScriptDriver Pdriver("graph.ps");     // declare a PostScript driver
    Gprocess.attachDriver(Pdriver);              // Attach driver to process

    Gprocess.setAxisRange(-3.0,3.0,-2.0,2.0);    // set plotting ranges
    Gprocess.title("Plot of function sin(x*x)"); // label the plot
    Gprocess.labelX(" X ");
    Gprocess.labelY(" Y ");

    Gprocess.plot(x,y,n);                       // do the plotting
    Gprocess.frame();                           // "frame" the plot

    Gprocess.detachDriver();                    // detach the driver

    delete [] x;                         // clean up
    delete [] y;

    std::cout << " Program Complete :  See graph.ps for output. "    << std::endl <<std::endl;
    return 0;
}
 
