//
//******************************************************************************
//                    CAMGRAPH.H
//******************************************************************************
//

#include <iostream>
#include <cstdlib>
#include <cstring>


//
//********************************************************************************
//
//            Chris Anderson (C) UCLA
//
//            Mon Apr 29 20:43:33 1996
//
//********************************************************************************
//
//
//  
//
#ifndef CAMGRAPHICS_
#define CAMGRAPHICS_

#ifndef  UCDRIVER_
class UCdriver;
#endif
#ifndef UCPLOT_
class UCplot;
#endif
#ifndef UCCONTOUR_
class UCcontour;
#endif
#ifndef UCSURFACE_
class UCsurface;
#endif

#include "camgraphimpexp.h"

class CAMgraphicsState;

class __IMPEXP__ CAMgraphics
{

public :

    static double  frameLeft;
    static double  frameRight;
    static double  frameBottom;
    static double  frameTop;
    static int  plotRegionIndex;
    static int  plotRegionRows;
    static int  plotRegionIndexBound;
    static int  defaultDriverFlag;
    static UCdriver*    OutputDeviceDriver;
    static UCplot**     UCplotPointerArray;
    static UCcontour**  UCcontourPointerArray;
    static UCsurface**  UCsurfacePointerArray;

    CAMgraphics();
    CAMgraphics(const CAMgraphics& A);

    ~CAMgraphics();
    void operator = ( const CAMgraphics& A);

//
//  Output 
//
    friend std::ostream& operator <<(std::ostream& out_stream, const CAMgraphics& A);
//
//  Enumerations
//
//
//  Axis Auto Scaling
//

    enum {AUTO_OFF ,AUTO  }; 
//
//  Label Type
//

    enum {FLOATING_POINT ,SCIENTIFIC  }; 
//
//  Axis Type Commands
//

    enum {GRID ,PERIMETER ,FLOATING  }; 
//
//  Axis Scale Type
//

    enum {LIN ,LOG  }; 
//
//  Plot Styles
//

    enum {CURVE ,POINTS ,CURVE_AND_POINTS  }; 
//
//  Colors
//

    enum {BLACK ,DARK_GREY ,LIGHT_GREY ,BLUE ,LIGHT_BLUE ,GREEN ,LIGHT_GREEN ,CYAN ,LIGHT_CYAN ,RED ,LIGHT_RED ,MAGENTA ,LIGHT_MAGENTA ,ORANGE ,YELLOW ,WHITE ,USER_RGB  }; 
//
//  Dash Patterns
//

    enum {SOLID = 0 ,DASH ,DOUBLE_DASH ,DASH_DOT ,DASH_DOUBLE_DOT ,DOTS ,USER_DASH  }; 
//
//  Frame and Sub Plot Manipulation
//
    static void  open();
    static void  open(UCdriver* d);
    static void  open(const char* fileName);
    static void  close();
    static void  frame();
    static void  setFrame(double fLeft, double fRight, double fBottom, double fTop);
    static void  subplotOn(int m, int n);
    static void  subplotOff();
    static void  subplot(int i, int j);
//
//  Title and Axis Label Manipulation
//
    static void  drawAxis();
    static void  title(const char*s, double size = 0);
    static void  labelX(const char*s, double size = 0);
    static void  labelY(const char*s, double size = 0);
    static void  setLabelFormat(int t, int w, int p);
    static void  setLabelType(int t);
    static void  setLabelWidth(int w);
    static void  setLabelPrecision(int p);
    static void  setLabelCharSize(double s);
    static void  setTicks(int majorX,int minorX,int majorY,int minorY);
    static void  setXTicks(int majorX);
    static void  setYTicks(int majorY);
    static void  setXTicks(int majorX,int minorX);
    static void  setYTicks(int majorY,int minorY);
    static void  getTicks(int& majorX,int& minorX,int& majorY,int& minorY);
    static void  getXTicks(int& majorX);
    static void  getYTicks(int& majorY);
    static void  getXTicks(int& majorX,int& minorX);
    static void  getYTicks(int& majorY,int& minorY);
//
//  Axis Manipulation
//
    static void  axis(int auto_flag);
    static void  axisAutoScaleOff(){axis(AUTO_OFF);};
    static void  axisAutoScaleOn(){axis(AUTO);};
    static void  axis(double x_min, double x_max, double y_min, double y_max);
    static void  setAxisRange(double x_min, double x_max, double y_min, double y_max)
     {axis(x_min,x_max,y_min,y_max);};
    static int   getAutoScaleFlag();
    static void  xAxisOn();
    static void  yAxisOn();
    static void  axisOn();
    static void  xAxisOff();
    static void  yAxisOff();
    static void  axisOff();
    static int   getAxisFlag();
    static int   getXAxisFlag();
    static int   getYAxisFlag();
    static void  xLabelsOn();
    static void  yLabelsOn();
    static void  labelsOn();
    static void  xLabelsOff();
    static void  yLabelsOff();
    static void  labelsOff();
    static int   getLabelsFlag();
    static int   getXLabelsFlag();
    static int   getYLabelsFlag();
    static void  setXAxisType(int t);
    static void  setYAxisType(int t);
    static void  setIntercepts(double x, double y);
    static void  setXIntercept(double x);
    static void  setYIntercept(double y);
    static void  setAxisColor(int c);
    static void  setAxisColor(double *rgb);
    static void  setXAxisScaleType(int s);
    static void  setYAxisScaleType(int s);
    static int   getXAxisScaleType();
    static int   getYAxisScaleType();

//
//  Line and Point Style Manipulation
//
    static void  setLineColor(int c);
    static void  setLineColor(double *rgb);
    static void  setDashPattern(int d);
    static void  setUserDashPattern(int d);
    static void  setLineWidth(double w);
    static void  setPointSize(double s);
    static void  setPointFont(const char*s);

    static void  setPlotLineColor(int c);
    static void  setPlotLineColor(double *rgb);
    static void  setPlotDashPattern(int d);
    static void  setPlotLineWidth(double w);
    static void  setPlotPointSize(double s);
    static void  setPlotPointFont(const char*s);



//
//  Text Drawing Routine
//
    static void  drawString(double x, double y, const char*s, double size = 0);

    static void  setTextColor(int c);
    static void  setTextColor(double *rgb);

    static void  setTextAlign(double horiz, double vert);
//
//  2D Plot Member Functions
//
    static void  setPlotStyle(int s);
    static void  setPointType(char p);

    static void  setPlotLineStyle(int s);
    static void  setPlotPointType(char p);

    static int   getPlotStyle();
    static char  getPointType();

    static void  plot();
    static void  plot(double *y, long n);
    static void  plot(double *y, long n, int p_arg);
    static void  plot(double *y, long n, int p_arg, int p_style);
    static void  plot(double *x, double *y, long n);
    static void  plot(double *x, double *y, long n, int p_arg);
    static void  plot(double *x, double *y, long n, int p_arg, int p_style);
    static void  plot(double (*f)(double x));
    static void  plot(double (*f)(double x), int p_arg);
    static void  plot(double (*f)(double x), int p_arg, int p_style);
    static void  plot(double (*f)(double x), double x_min, double x_max);
    static void  plot(double (*f)(double x), double x_min, double x_max, int p_arg);
    static void  plot(double (*f)(double x), double x_min, double x_max, int p_arg, int p_style);
    static void  plot(double (*f)(double x), double x_min, double x_max, double y_min, double y_max);
    static void  plot(double (*f)(double x), double x_min, double x_max, double y_min, double y_max, int p_arg);
    static void  plot(double (*f)(double x), double x_min, double x_max, double y_min, double y_max, int p_arg, int p_style);
//
//  Member Functions For Combined Surface and Contour Routines
//
    static void  fortranArrayFlagOn();
    static void  fortranArrayFlagOff();
    static int   getFortranArrayFlag();
//
//  Contour Member Functions
//
    static void  contour();
    static void  contour(double *dataPointer, int n, int m);
    static void  contour(double *dataPointer, int n, int m, int nContour);
    static void  contour(double *dataPointer, int n, int m, long nContour);
    static void  contour(double *dataPointer, int n, int m, double increment);
    static void  contour(double *dataPointer, int n, int m, double low_value, double high_value);
    static void  contour(double *dataPointer, int n, int m, int nCountour, double low_value, double high_value);
    static void  contour(double *dataPointer, int n, int m, long nCountour, double low_value, double high_value);
    static void  contour(double *dataPointer, int n, int m, double increment, double low_value, double high_value);
    static void  contour(double *dataPointer, int n, int m, double* contour_values, int nContour);
    static void  autoContourOn();
    static void  autoContourOff();
    static void  lineLabelsOn();
    static void  lineLabelsOff();
    static void  highLowLabelsOn();
    static void  highLowLabelsOff();
    static void  backgroundOn();
    static void  backgroundOff();
    static int   getBackgroundFlag();
    static void  scaledFrameOn();
    static void  scaledFrameOff();

    static void  contourLineLabelsOn();
    static void  contourLineLabelsOff();
    static void  contourHighLowLabelsOn();
    static void  contourHighLowLabelsOff();
    static void  contourBackgroundOn();
    static void  contourBackgroundOff();
    static void  contourScaledFrameOn();
    static void  contourScaledFrameOff();

    static void  setContourLevel(long nContour);
    static void  setContourLevel(int nContour);
    static void  setContourLevel(double increment);
    static void  setContourLevel(float increment);
    static void  setContourLevel(double low_value, double high_value);
    static void  setContourLevel(int nContour, double low_value, double high_value);
    static void  setContourLevel(long nContour, double low_value, double high_value);
    static void  setContourLevel(double increment, double low_value, double high_value);
    static void  setContourLevel(double* values, long nContour);
    static void  setContourLineColor(int colorIndex);
//
//  Surface Plot Member Functions
//
    static void  surface();
    static void  surface(double* A, long r, long c);
    static void  surface(double* A, long r, long c, double *x, double *y);
    static void  surface(double (*data)(long,long), long r, long c, double *x, double *y);

    static void  setViewPoint(double x, double y, double z);
    static void  setViewPoint(double *vp);
    static void  setFocus(double x, double y, double z);
    static void  setFocus(double* f);
    static void  setScaleFactor(double sf);

    static void  setSurfaceViewPoint(double x, double y, double z);
    static void  setSurfaceFocus(double x, double y, double z);
    static void  setSurfaceScaleFactor(double sf);

    static void  setXOffset(double xo);
    static void  setYOffset(double yo);
//
//  CAMgraphicsState manipulation
//
	 static void setState(const CAMgraphicsState& S);
    static void getState(CAMgraphicsState& S);
};
//
//  Class to store CAMgraphics state
//
class __IMPEXP__ CAMgraphicsState
{

public :

    CAMgraphicsState();
    CAMgraphicsState(UCdriver* D);

    ~CAMgraphicsState();

    CAMgraphicsState(const CAMgraphicsState& S);
    void operator=(const CAMgraphicsState& S);

    void setDriver(UCdriver* D);

    double  frameLeft;
    double  frameRight;
    double  frameBottom;
    double  frameTop;
    int  plotRegionIndex;
    int  plotRegionRows;
    int  plotRegionIndexBound;
    int  defaultDriverFlag;
    UCdriver*    OutputDeviceDriver;
    UCplot**     UCplotPointerArray;
    UCcontour**  UCcontourPointerArray;
    UCsurface**  UCsurfacePointerArray;
};
#endif
//
//********************************************************************************
//                     Header File End
//********************************************************************************
//

 
