#ifndef CAMGRAPHICSPROCESS__
#define CAMGRAPHICSPROCESS__
//
//######################################################################
//
//            Chris Anderson (C) UCLA
//
//                 Sept. 17, 1996
//
//######################################################################
//
//
//

#include <iostream>
#include <cstdlib>
#include <cstring>

#ifndef CAMGRAPHICSDRIVER__
class CAMgraphicsDriver;
#endif

#include "camgraphimpexp.h"

class __IMPEXP__ CAMgraphicsProcess
{

public :

	CAMgraphicsProcess();


	virtual ~CAMgraphicsProcess(){};
    
    virtual void attachDriver(CAMgraphicsDriver* O);
    virtual void attachDriver(CAMgraphicsDriver& O){attachDriver(&O);};
    virtual void detachDriver();
    CAMgraphicsDriver* getDriver(){return ODriver;};

    virtual void frame();
    virtual void reset();

    void  plot();
    void  plot(double* y, long n);
    void  plot(double *y, long n, int p_arg);
    void  plot(double *y, long n, int p_arg, int p_style);
    void  plot(double *x, double *y, long n);
    void  plot(double *x, double *y, long n, int p_arg);
    void  plot(double *x, double *y, long n, int p_arg, int p_style);

    void  region(double *x, double *y, long n);
    void  region(double *x, double *y, long n, int color, double *rgb);

	void contour();
	void contour(double *z, long m, long n);
	void contour(double *z, long m, long n, int n_c);
	void contour(double *z, long m, long n, double c_inc);
	void contour(double *z, long m, long n, double c_min, double c_max);
	void contour(double *z, long m, long n, int n_c, double c_min, double c_max);
	void contour(double* z, long m, long n, double c_inc, double c_min, double c_max);
	void contour(double *z, long m, long n, double* c_values, int n_c);
	void setContourLineColor(int colorIndex);

	void surface();
	void surface(double* z, long  m, long n);
	void surface(double *z, long m, long n, double* x, double* y);

	void drawString(double x, double y, const char* S);
	void drawString(double x, double y, const char* S, double size);

    void setTextColor(int iColor);
    void setTextColor(double* rgb);
    void setTextAlign(double horiz, double vert);

	void title(const char* S);
	void title(const char* S, double size);
	void labelX(const char* S);
	void labelX(const char* S, double size);
	void labelY(const char* S);
	void labelY(const char* S, double size);


	void setFrame(double left, double right, double bottom, double top);
	void subplotOn(long m, long n);
	void subplot(long m, long n);
	void subplotOff();
	void axisAutoScaleOn();
	void axisAutoScaleOff();
    
    void setAxisRange(double xmin, double xmax, double ymin, double ymax);
    void drawAxis();
    void setTicks(long Mx, long mx, long Nx, long nx);
    void setXTicks(long Mx, long mx);
    void setYTicks(long Nx, long nx);
    void xAxisOn();
    void xAxisOff();
    void yAxisOn();
    void yAxisOff();
    void axisOn();
    void axisOff();
    void xLabelsOn();
    void xLabelsOff();
    void yLabelsOn();
    void yLabelsOff();
    void labelsOn();
    void labelsOff();

    void setXAxisType(int t);
    void setYAxisType(int t);
    void setIntercepts(double x, double y);
    void setXIntercept(double x);
    void setYIntercept(double y);
    void setAxisColor(int iColor);
    void setAxisColor(double* rgb);
    void setAxisLabelType(int t);
    void setAxisLabelWidth(int w);
    void setAxisLabelPrecision(int  p);
    void setAxisLabelCharSize(double size);
    void setAxisLabelFormat(int t , int w, int p);

    void setPlotLineStyle(int s);
    void setPlotLineColor(int c);
    void setPlotLineColor(double* rgb);
    void setPlotDashPattern(int d);
    void setPlotLineWidth(double w);
    void setPlotPointType(char p);
    void setPlotPointSize(double p);
    void setPlotPointFont(const char* S);

    void restorePlotDefaults();

    void setContourLevel(int n_c);
    void setContourLevel(double c_inc);
    void setContourLevel(double c_min, double c_max);
    void setContourLevel(int n_c,double c_min, double c_max);
    void setContourLevel(double c_inc,double c_min, double c_max);
    void setContourLevel(double* c_values, int n_c);
    void autoContourOn();
    void autoContourOff();
    void contourLineLabelsOn();
    void contourLineLabelsOff();
    void contourHighLowLabelsOn();
    void contourHighLowLabelsOff();
    void contourBackgroundOn();
    void contourBackgroundOff();
    void contourScaledFrameOn();
    void contourScaledFrameOff();
    void setSurfaceViewPoint(double vx, double vy ,double vz);
    void setSurfaceFocus(double fx, double fy ,double fz);
    void setSurfaceScaleFactor(double s);

//
//  Enumerations
//
//
//  Axis Auto Scaling
//
    enum {AUTO_OFF ,AUTO};
//
//  Label Type
//
    enum {FLOATING_POINT ,SCIENTIFIC};
//
//  Axis Type Commands
//
    enum {GRID ,PERIMETER ,FLOATING  }; 
//
//  Axis Scale Type
//
    enum {LIN ,LOG};
//
//  Plot Styles
//
    enum {CURVE ,POINTS ,CURVE_AND_POINTS  }; 
//
//  Colors
//
    enum {BLACK ,DARK_GREY ,LIGHT_GREY ,BLUE ,LIGHT_BLUE ,
    GREEN ,LIGHT_GREEN ,CYAN ,LIGHT_CYAN ,RED ,LIGHT_RED ,
    MAGENTA ,LIGHT_MAGENTA ,ORANGE ,YELLOW ,WHITE ,USER_RGB};
//
//  Dash Patterns
//

    enum {SOLID = 0 ,DASH ,DOUBLE_DASH ,DASH_DOT ,DASH_DOUBLE_DOT ,DOTS ,USER_DASH  }; 
//

public :

    CAMgraphicsDriver* ODriver;

};
#endif
 
