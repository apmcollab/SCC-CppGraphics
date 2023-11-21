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
#include <cmath>
#include <stdio.h>
#include <iostream>
#include "../CAMgraphics.h"

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

    CAMgraphics camGraphics;
    
    camGraphics.open("PlotStyleSample");              // open file graph.ps for output
    //
    // First frame;  using different plot "styles"
    //
    camGraphics.setAxisRange(-3.0,3.0,-2.0,2.0);             // set plotting ranges
    camGraphics.title("Plots Using Different Plot Styles");  // label the plot
    camGraphics.labelX(" X ");
    camGraphics.labelY(" Y ");

    camGraphics.plot(x,y1,n);                    // solid line (default)
    camGraphics.plot(x,y2,n,'+');                // + markers

                                              // + markers and solid line

    camGraphics.plot(x,y3,n,'+',camGraphics.CURVE_AND_POINTS);

    camGraphics.frame();                           // "frame" the plot
    //
    // Second frame; using different plot line "styles"
    //
    camGraphics.setAxisRange(-3.0,3.0,-2.0,2.0);            // set plotting ranges
    camGraphics.title("Plots Using Different Line Styles"); // label the plot
    camGraphics.labelX(" X ");
    camGraphics.labelY(" Y ");

    camGraphics.setLineColor(camGraphics.RED);     // Red line
    camGraphics.plot(x,y1,n);

    camGraphics.setLineWidth(0.004);
    camGraphics.setLineColor(camGraphics.BLACK);   // Black dashed line
    camGraphics.setDashPattern(camGraphics.DASH);
    camGraphics.plot(x,y2,n);

    camGraphics.setLineWidth(0.004);
    camGraphics.setLineColor(camGraphics.BLUE);   // Blue dash-dot line
    camGraphics.setDashPattern(camGraphics.DASH_DOT);
    camGraphics.plot(x,y3,n);

    camGraphics.frame();                           // "frame" the plot


    camGraphics.close();                            // close

    delete [] x;                         // clean up
    delete [] y1;
    delete [] y2;
    delete [] y3;

    std::cout << "   Program Complete "    << std::endl << std::endl;
	return 0;
}
 
