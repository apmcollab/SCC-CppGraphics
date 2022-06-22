//
//######################################################################
//            CAMgraphics Sample Program  #2
//
// Chris Andersion (C) UCLA 1996                                10/6//96
//                                                              04/04/07
//######################################################################
//
/*
	Plots various trigonometric functions over [-3.3] using
    different plot and line styles.
*/
#include "camgraph.h"
#include <cmath>
#include <stdio.h>
#include <iostream>

//
// Functions to be plotted
//
double f1(double x){ return sin(x);};
double f2(double x){ return cos(x);};
double f3(double x){ return cos(2.0*x);};

int main()
{
    double a  = -3.0;                     // create data for line plot
    double b  =  3.0;
    long   n  =  50;                     
    double h  = (b-a)/double(n-1);

    double* x  = new double[n];
    double* y1 = new double[n];
    double* y2 = new double[n];
    double* y3 = new double[n];

    int i;
    for(i=0; i < n; i++)
    {
    x[i] = a + double(i)*h;
    y1[i] = f1(x[i]);
    y2[i] = f2(x[i]);
    y3[i] = f3(x[i]);
    }

    CAMgraphics::open("graph.ps");              // open file graph.ps for output
    //
    // First frame;  using different plot "styles"
    //
    CAMgraphics::setAxisRange(-3.0,3.0,-2.0,2.0);             // set plotting ranges
    CAMgraphics::title("Plots Using Different Plot Styles");  // label the plot
    CAMgraphics::labelX(" X ");
    CAMgraphics::labelY(" Y ");

    CAMgraphics::plot(x,y1,n);                    // solid line (default)
    CAMgraphics::plot(x,y2,n,'+');                // + markers

                                              // + markers and solid line

    CAMgraphics::plot(x,y3,n,'+',CAMgraphics::CURVE_AND_POINTS);

    CAMgraphics::frame();                           // "frame" the plot
    //
    // Second frame; using different plot line "styles"
    //
    CAMgraphics::setAxisRange(-3.0,3.0,-2.0,2.0);            // set plotting ranges
    CAMgraphics::title("Plots Using Different Line Styles"); // label the plot
    CAMgraphics::labelX(" X ");
    CAMgraphics::labelY(" Y ");

    CAMgraphics::setLineColor(CAMgraphics::RED);     // Red line
    CAMgraphics::plot(x,y1,n);

    CAMgraphics::setLineColor(CAMgraphics::BLACK);   // Black dashed line
    CAMgraphics::setDashPattern(CAMgraphics::DASH);
    CAMgraphics::plot(x,y2,n);

    CAMgraphics::setLineColor(CAMgraphics::BLUE);   // Blue dash-dot line
    CAMgraphics::setDashPattern(CAMgraphics::DASH_DOT);
    CAMgraphics::plot(x,y3,n);

    CAMgraphics::frame();                           // "frame" the plot


    CAMgraphics::close();                            // close

    delete [] x;                         // clean up
    delete [] y1;
    delete [] y2;
    delete [] y3;

    std::cout << "   Program Complete "    << std::endl << std::endl;
	return 0;
}
 
