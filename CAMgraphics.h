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
/*
#############################################################################
#
# Copyright  2024 Chris Anderson
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the Lesser GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# For a copy of the GNU General Public License see
# <http://www.gnu.org/licenses/>.
#
#############################################################################
*/ 
//
#include <vector>
#include <string>

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


class  CAMgraphics
{

public :

    double  frameLeft;
    double  frameRight;
    double  frameBottom;
    double  frameTop;
    int     plotRegionIndex;
    int     plotRegionRows;
    int     plotRegionIndexBound;
    int     defaultDriverFlag;

    UCdriver*                OutputDeviceDriver;
    std::vector<UCplot*>      UCplotPointerArray;
    std::vector<UCcontour*>   UCcontourPointerArray;
    std::vector<UCsurface*>   UCsurfacePointerArray;

    CAMgraphics();
    CAMgraphics(const CAMgraphics& A);

    ~CAMgraphics();
    void operator = ( const CAMgraphics& A);

    void initialize();
    void initialize(const CAMgraphics& A);

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

    enum {AUTO_OFF ,AUTO};
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

    enum {BLACK ,DARK_GREY ,LIGHT_GREY ,BLUE ,LIGHT_BLUE ,GREEN ,LIGHT_GREEN ,CYAN ,LIGHT_CYAN,
    	  RED ,LIGHT_RED ,MAGENTA ,LIGHT_MAGENTA ,ORANGE ,YELLOW ,WHITE ,USER_RGB,NONE};
//
//  Dash Patterns
//

    enum {SOLID = 0 ,DASH ,DOUBLE_DASH ,DASH_DOT ,DASH_DOUBLE_DOT ,DOTS ,USER_DASH  }; 

    UCdriver* getDriver() {return this->OutputDeviceDriver;}

    std::string getDriverTypeName();
//
//  Frame and Sub Plot Manipulation
//
    void  open();
    void  open(UCdriver* d);
    void  open(const std::string& fileName);

    // Suppress addition index value 0 prepended to name of first
    // page produced. For drivers in which separate frames are
    // output as separate image pages).

    void  clearMultiPageFlag();

    void  setMultiPageFlag(bool multiFrameFlag = true);

    void  close();


    void  frame();
    void  setFrame(double fLeft, double fRight, double fBottom, double fTop);
    void  subplotOn(int m, int n);
    void  subplotOff();
    void  subplot(int i, int j);
//
//  Title and Axis Label Manipulation
//
    void  drawAxis();
    void  title(const std::string&  s, double size = 0);
    void  labelX(const std::string& s, double size = 0);
    void  labelY(const std::string& s, double size = 0);
    void  setLabelFormat(int t, int w, int p);
    void  setLabelType(int t);
    void  setLabelWidth(int w);
    void  setLabelPrecision(int p);
    void  setLabelCharSize(double s);
    void  setTicks(int majorX,int minorX,int majorY,int minorY);
    void  setXTicks(int majorX);
    void  setYTicks(int majorY);
    void  setXTicks(int majorX,int minorX);
    void  setYTicks(int majorY,int minorY);
    void  getTicks(int& majorX,int& minorX,int& majorY,int& minorY);
    void  getXTicks(int& majorX);
    void  getYTicks(int& majorY);
    void  getXTicks(int& majorX,int& minorX);
    void  getYTicks(int& majorY,int& minorY);
//
//  Axis Manipulation
//
    void  axis(int auto_flag);
    void  axisAutoScaleOff(){axis(AUTO_OFF);};
    void  axisAutoScaleOn(){axis(AUTO);};
    void  axis(double x_min, double x_max, double y_min, double y_max);
    void  setAxisRange(double x_min, double x_max, double y_min, double y_max)
     {axis(x_min,x_max,y_min,y_max);};
    int   getAutoScaleFlag();
    void  xAxisOn();
    void  yAxisOn();
    void  axisOn();
    void  xAxisOff();
    void  yAxisOff();
    void  axisOff();
    int   getAxisFlag();
    int   getXAxisFlag();
    int   getYAxisFlag();
    void  xLabelsOn();
    void  yLabelsOn();
    void  labelsOn();
    void  xLabelsOff();
    void  yLabelsOff();
    void  labelsOff();
    int   getLabelsFlag();
    int   getXLabelsFlag();
    int   getYLabelsFlag();
    void  setXAxisType(int t);
    void  setYAxisType(int t);
    void  setIntercepts(double x, double y);
    void  setXIntercept(double x);
    void  setYIntercept(double y);
    void  setAxisColor(int c);
    void  setAxisColor(const std::vector<double>& rgb);
    void  setXAxisScaleType(int s);
    void  setYAxisScaleType(int s);
    int   getXAxisScaleType();
    int   getYAxisScaleType();

//
//  Line and Point Style Manipulation
//
    void  setLineColor(int c);
    void  setLineColor(const std::vector<double>& rgb);
    void  setDashPattern(int d);
    void  setUserDashPattern(int d);
    void  setLineWidth(double w);
    void  setPointSize(double s);
    void  setPointFont(const std::string& s);

    void  setPlotLineColor(int c);
    void  setPlotLineColor(const std::vector<double>& rgb);
    void  setPlotDashPattern(int d);
    void  setPlotLineWidth(double w);
    void  setPlotPointSize(double s);
    void  setPlotPointFont(const std::string& s);

//
//  Text Drawing Routine
//
    void  drawString(double x, double y, const std::string& s, double size = 0);

    void  setTextColor(int c);
    void  setTextColor(const std::vector<double>& rgb);

    void  setTextAlign(double horiz, double vert);
//
//  2D Plot Member Functions
//
    void  setPlotStyle(int s);
    void  setPointType(char p);

    void  setPlotLineStyle(int s);
    void  setPlotPointType(char p);

    int   getPlotStyle();
    char  getPointType();

    void  plot();
    void  plot(double *y, long n);
    void  plot(double *y, long n, int p_arg);
    void  plot(double *y, long n, int p_arg, int p_style);
    void  plot(double *x, double *y, long n);
    void  plot(double *x, double *y, long n, int p_arg);
    void  plot(double *x, double *y, long n, int p_arg, int p_style);
    void  plot(double (*f)(double x));
    void  plot(double (*f)(double x), int p_arg);
    void  plot(double (*f)(double x), int p_arg, int p_style);
    void  plot(double (*f)(double x), double x_min, double x_max);
    void  plot(double (*f)(double x), double x_min, double x_max, int p_arg);
    void  plot(double (*f)(double x), double x_min, double x_max, int p_arg, int p_style);
    void  plot(double (*f)(double x), double x_min, double x_max, double y_min, double y_max);
    void  plot(double (*f)(double x), double x_min, double x_max, double y_min, double y_max, int p_arg);
    void  plot(double (*f)(double x), double x_min, double x_max, double y_min, double y_max, int p_arg, int p_style);

    void  region(double *X, double *Y, long npoints);
    void  region(double *X, double *Y, long npoints, int color, const std::vector<double>& RGB);
//
//  Member Functions For Combined Surface and Contour Routines
//
    void  fortranArrayFlagOn();
    void  fortranArrayFlagOff();
    int   getFortranArrayFlag();
//
//  Contour Member Functions
//
    void  contour();
    void  contour(double *dataPointer, int n, int m);
    void  contour(double *dataPointer, int n, int m, int nContour);
    void  contour(double *dataPointer, int n, int m, long nContour);
    void  contour(double *dataPointer, int n, int m, double increment);
    void  contour(double *dataPointer, int n, int m, double low_value, double high_value);
    void  contour(double *dataPointer, int n, int m, int nCountour, double low_value, double high_value);
    void  contour(double *dataPointer, int n, int m, long nCountour, double low_value, double high_value);
    void  contour(double *dataPointer, int n, int m, double increment, double low_value, double high_value);
    void  contour(double *dataPointer, int n, int m, const std::vector<double>&  contour_values, int nContour);
    void  autoContourOn();
    void  autoContourOff();
    void  lineLabelsOn();
    void  lineLabelsOff();
    void  highLowLabelsOn();
    void  highLowLabelsOff();
    void  backgroundOn();
    void  backgroundOff();
    int   getBackgroundFlag();
    void  scaledFrameOn();
    void  scaledFrameOff();

    void  contourLineLabelsOn();
    void  contourLineLabelsOff();
    void  contourHighLowLabelsOn();
    void  contourHighLowLabelsOff();
    void  contourBackgroundOn();
    void  contourBackgroundOff();
    void  contourScaledFrameOn();
    void  contourScaledFrameOff();

    void  setContourLevel(long nContour);
    void  setContourLevel(int nContour);
    void  setContourLevel(double increment);
    void  setContourLevel(float increment);
    void  setContourLevel(double low_value, double high_value);
    void  setContourLevel(int nContour, double low_value, double high_value);
    void  setContourLevel(long nContour, double low_value, double high_value);
    void  setContourLevel(double increment, double low_value, double high_value);
    void  setContourLevel(const std::vector<double>& values, long nContour);
    void  setContourLineColor(int colorIndex);
//
//  Surface Plot Member Functions
//
    void  surface();
    void  surface(double* A, long r, long c);
    void  surface(double* A, long r, long c, double *x, double *y);
    void  surface(double (*data)(long,long), long r, long c, double *x, double *y);

    void  setViewPoint(double x, double y, double z);
    void  setViewPoint(double *vp);
    void  setFocus(double x, double y, double z);
    void  setFocus(double* f);
    void  setScaleFactor(double sf);

    void  setSurfaceViewPoint(double x, double y, double z);
    void  setSurfaceFocus(double x, double y, double z);
    void  setSurfaceScaleFactor(double sf);

    void  setXOffset(double xo);
    void  setYOffset(double yo);
//
//  CAMgraphicsState manipulation
//
//  void setState(const CAMgraphicsState& S);
//  void getState(CAMgraphicsState& S);
};

#endif
//********************************************************************************
//                     Header File End
//********************************************************************************
//

 
