//
//######################################################################
//            CAMgraphicsProcess Sample Program  #2
//
// Chris Andersion (C) UCLA 1996                                10/6//96
//                                                              04/05/07
//######################################################################
//
/*
	Plots various trigonometric functions over [-3.3] using
    different plot and line styles.
*/
#include "gprocess.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
using namespace std;
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

    CAMgraphicsProcess Gprocess;              // declare a graphics process
    CAMpostScriptDriver Pdriver("graph.ps");  // declare a PostScript driver
    Gprocess.attachDriver(Pdriver);           // Attach driver to process
    //
    // First frame;  using different plot "styles"
    //
    Gprocess.setAxisRange(-3.0,3.0,-2.0,2.0);             // set plotting ranges
    Gprocess.title("Plots Using Different Plot Styles");  // label the plot
    Gprocess.labelX(" X ");
    Gprocess.labelY(" Y ");

    Gprocess.plot(x,y1,n);                    // solid line (default)
    Gprocess.plot(x,y2,n,'+');                // + markers

                                              // + markers and solid line

    Gprocess.plot(x,y3,n,'+',CAMgraphicsProcess::CURVE_AND_POINTS);

    Gprocess.frame();                           // "frame" the plot
    //
    // Second frame; using different plot line "styles"
    //
    Gprocess.setAxisRange(-3.0,3.0,-2.0,2.0);            // set plotting ranges
    Gprocess.title("Plots Using Different Line Styles"); // label the plot
    Gprocess.labelX(" X ");
    Gprocess.labelY(" Y ");

    Gprocess.setPlotLineColor(CAMgraphicsProcess::RED);     // Red line
    Gprocess.plot(x,y1,n);

    Gprocess.setPlotLineColor(CAMgraphicsProcess::BLACK);   // Black dashed line
    Gprocess.setPlotDashPattern(CAMgraphicsProcess::DASH);
    Gprocess.plot(x,y2,n);

    Gprocess.setPlotLineColor(CAMgraphicsProcess::BLUE);   // Blue dash-dot line
    Gprocess.setPlotDashPattern(CAMgraphicsProcess::DASH_DOT);
    Gprocess.plot(x,y3,n);

    Gprocess.frame();                           // "frame" the plot


    Gprocess.detachDriver();                    // detach the driver

    delete [] x;                         // clean up
    delete [] y1;
    delete [] y2;
    delete [] y3;

    cout << " Program Complete :  See graph.ps for output. "    << endl <<endl;
    return 0;
}
 
