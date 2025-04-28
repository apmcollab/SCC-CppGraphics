#include "CAMgraphics.h"
#include "UC2dgraph.h"
#include "UC3dgraph.h"
#include "UCcontour.h"
#include "UCdriver.h"
#include "UCdriver.h"

#include "UCgraph.h"
#include "UCplot.h"
#include "UCsurface.h"

#include "SVGdriver.h"
#include "UCdriver_ps.h"

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
//******************************************************************************
//                          CAMGRAPH.CPP
//******************************************************************************
//
//********************************************************************************
//                          CONSTRUCTORS
//********************************************************************************
//
//********************************************************************************

//
//********************************************************************************
//               
//********************************************************************************
//
CAMgraphics::CAMgraphics()
{
    frameLeft             = 0.0;
    frameRight            = 0.0;
    frameBottom           = 0.0;
    frameTop              = 0.0;
    plotRegionIndex       = 0;
    plotRegionRows        = 0;
    plotRegionIndexBound  = 0;
    defaultDriverFlag     = 0;
    OutputDeviceDriver    = nullptr;

    UCplotPointerArray.clear();
    UCcontourPointerArray.clear();
    UCsurfacePointerArray.clear();
}

void CAMgraphics::initialize()
{
	if(UCplotPointerArray.size() != 0)
	{
		for(size_t k = 0; k < UCplotPointerArray.size(); k++)
		{delete UCplotPointerArray[k];}
		UCplotPointerArray.clear();
	}

    if(UCcontourPointerArray.size() != 0)
	{
		for(size_t k = 0; k < UCcontourPointerArray.size(); k++)
		{delete UCcontourPointerArray[k];}
		UCcontourPointerArray.clear();
	}

    if(UCsurfacePointerArray.size() != 0)
	{
		for(size_t k = 0; k < UCsurfacePointerArray.size(); k++)
		{delete UCsurfacePointerArray[k];}
		UCsurfacePointerArray.clear();
	}

    if(defaultDriverFlag == 1)
    {
    delete OutputDeviceDriver;
    OutputDeviceDriver    = nullptr;
    }

    frameLeft             = 0.0;
    frameRight            = 0.0;
    frameBottom           = 0.0;
    frameTop              = 0.0;
    plotRegionIndex       = 0;
    plotRegionRows        = 0;
    plotRegionIndexBound  = 0;
    defaultDriverFlag     = 0;
}
//
//********************************************************************************
//                    DESTRUCTOR
//********************************************************************************
//
CAMgraphics::~CAMgraphics()
{
	if(UCplotPointerArray.size() != 0)
	{
		for(size_t k = 0; k < UCplotPointerArray.size(); k++)
		{delete UCplotPointerArray[k];}
	}

    if(UCcontourPointerArray.size() != 0)
	{
		for(size_t k = 0; k < UCcontourPointerArray.size(); k++)
		{delete UCcontourPointerArray[k];}
	}


    if(UCsurfacePointerArray.size() != 0)
	{
		for(size_t k = 0; k < UCsurfacePointerArray.size(); k++)
		{delete UCsurfacePointerArray[k];}
	}

    if(defaultDriverFlag == 1)
    {
    delete OutputDeviceDriver;
    }
}


CAMgraphics::CAMgraphics(const CAMgraphics& S)
{
//
//  Pointers to plot/contour/surface instances
//  and associated driver are copied; instances are not
//  duplicated.
//
    UCplotPointerArray.clear();
    UCcontourPointerArray.clear();
    UCsurfacePointerArray.clear();

    UCplotPointerArray    = S.UCplotPointerArray;
    UCcontourPointerArray = S.UCcontourPointerArray;
    UCsurfacePointerArray = S.UCsurfacePointerArray;

    frameLeft             = S.frameLeft;
    frameRight            = S.frameRight;
    frameBottom           = S.frameBottom;
    frameTop              = S.frameTop;
    plotRegionIndexBound  = S.plotRegionIndexBound;
    plotRegionIndex       = S.plotRegionIndex ;
    plotRegionRows        = S.plotRegionRows;

    if(S.OutputDeviceDriver != nullptr)
    {
    defaultDriverFlag     = 0;
    OutputDeviceDriver    = S.OutputDeviceDriver;
    }
}


void CAMgraphics::operator=(const CAMgraphics& S)
{
//
//  Pointers to plot/contour/surface instances
//  and associated driver are copied; instances are not
//  duplicated.
//
    UCplotPointerArray.clear();
    UCcontourPointerArray.clear();
    UCsurfacePointerArray.clear();

    UCplotPointerArray    = S.UCplotPointerArray;
    UCcontourPointerArray = S.UCcontourPointerArray;
    UCsurfacePointerArray = S.UCsurfacePointerArray;

    frameLeft             = S.frameLeft;
    frameRight            = S.frameRight;
    frameBottom           = S.frameBottom;
    frameTop              = S.frameTop;
    plotRegionIndexBound  = S.plotRegionIndexBound;
    plotRegionIndex       = S.plotRegionIndex ;
    plotRegionRows        = S.plotRegionRows;

    if(S.OutputDeviceDriver != nullptr)
    {
    defaultDriverFlag     = 0;
    OutputDeviceDriver    = S.OutputDeviceDriver;
    }
}
//
//********************************************************************************
//                    MEMBER_FUNCTIONS
//********************************************************************************

void  CAMgraphics::open()
{
	initialize();
//
//  Set Defaults
//
    frameLeft             = 0.14;
    frameRight            = 0.94;
    frameBottom           = 0.1;
    frameTop              = 0.9;
    plotRegionIndex       = 1;
    plotRegionRows        = 1;
    plotRegionIndexBound  = 1;

//  Set default to scalable vector graphics driver (SVGdriver)

    defaultDriverFlag     = 1;
    OutputDeviceDriver    = new SVGdriver("graph",true);

    UCplotPointerArray.resize(plotRegionIndexBound);
    UCcontourPointerArray.resize(plotRegionIndexBound);
    UCsurfacePointerArray.resize(plotRegionIndexBound);

    UCplotPointerArray[0]    = new UCplot(OutputDeviceDriver);
    UCcontourPointerArray[0] = new UCcontour(OutputDeviceDriver);
    UCsurfacePointerArray[0] = new UCsurface(OutputDeviceDriver);

    setFrame(frameLeft,frameRight,frameBottom,frameTop);
}


void  CAMgraphics::open(UCdriver* d)
{
    initialize();
//
//  Set Defaults
//
    frameLeft             = 0.14;
    frameRight            = 0.94;
    frameBottom           = 0.1;
    frameTop              = 0.9;
    plotRegionIndex       = 1;
    plotRegionRows        = 1;
    plotRegionIndexBound  = 1;

    defaultDriverFlag     = 0;
    OutputDeviceDriver    = d;

    UCplotPointerArray.resize(plotRegionIndexBound);
    UCcontourPointerArray.resize(plotRegionIndexBound);
    UCsurfacePointerArray.resize(plotRegionIndexBound);

    UCplotPointerArray[0]    = new UCplot(OutputDeviceDriver);
    UCcontourPointerArray[0] = new UCcontour(OutputDeviceDriver);
    UCsurfacePointerArray[0] = new UCsurface(OutputDeviceDriver);

    setFrame(frameLeft,frameRight,frameBottom,frameTop);
}


void CAMgraphics::open(const std::string& fileName)
{
	initialize();
//
//  Set Defaults
//
    frameLeft             = 0.14;
    frameRight            = 0.94;
    frameBottom           = 0.1;
    frameTop              = 0.9;
    plotRegionIndex       = 1;
    plotRegionRows        = 1;
    plotRegionIndexBound  = 1;
//
//  Set Default to PostScript associated with file fileName
//
//  defaultDriverFlag     = 1;
//  OutputDeviceDriver     = new UCdriver_ps(fileName);

//
//  Set default to scalable vector graphics driver (SVGdriver)
//
    defaultDriverFlag     = 1;
    OutputDeviceDriver    = new SVGdriver(fileName);

    UCplotPointerArray.resize(plotRegionIndexBound);
    UCcontourPointerArray.resize(plotRegionIndexBound);
    UCsurfacePointerArray.resize(plotRegionIndexBound);
#include "SVGdriver.h"
    UCplotPointerArray[0]    = new UCplot(OutputDeviceDriver);
    UCcontourPointerArray[0] = new UCcontour(OutputDeviceDriver);
    UCsurfacePointerArray[0] = new UCsurface(OutputDeviceDriver);

    setFrame(frameLeft,frameRight,frameBottom,frameTop);
}

std::string CAMgraphics::getDriverTypeName()
{
    	if(this->OutputDeviceDriver != nullptr)
    	{
    		return this->OutputDeviceDriver->getDriverTypeName();
    	}
    	else
    	{
    		return std::string();
    	}
}

void  CAMgraphics::clearMultiPageFlag()
{
	if(OutputDeviceDriver->getDriverTypeName() == "SVGdriver")
	{
		((SVGdriver*)OutputDeviceDriver)->clearMultipleFrameFlag();
	}
}

void  CAMgraphics::setMultiPageFlag(bool val)
{
	((SVGdriver*)OutputDeviceDriver)->setMultipleFrameFlag(val);
}


void  CAMgraphics::close()
{
	 initialize();
}

void  CAMgraphics::frame()
{ 
    OutputDeviceDriver->frame();
}

void  CAMgraphics::setFrame(double fLeft, double fRight, double fBottom, double fTop)
{    
    if(plotRegionIndexBound == 1)
    {
    frameLeft   = fLeft;
    frameRight  = fRight;
    frameBottom = fBottom;
    frameTop    = fTop;
    UCplotPointerArray[plotRegionIndex-1]->set_frame(fLeft,fRight,fBottom,fTop);
    UCcontourPointerArray[plotRegionIndex-1]->set_frame(fLeft,fRight,fBottom,fTop); 
    UCsurfacePointerArray[plotRegionIndex-1]->set_frame(fLeft,fRight,fBottom,fTop);
    }
    else
    {
    int m = plotRegionRows;
    int n = plotRegionIndexBound/plotRegionRows;

    double hx = (frameRight - frameLeft)/double(n);
    double hy = (frameTop   - frameBottom)/double(m); 
        
    int j = int((plotRegionIndex-1)/plotRegionRows) + 1;
    int i = plotRegionIndex - (j-1)*plotRegionRows;
    double fL      = frameLeft   + (j-1)*hx + fLeft*hx;
    double fR      = frameLeft   + (j-1)*hx + fRight*hx; 
    double fB      = frameBottom + (m-i)*hy + fBottom*hy;
    double fT      = frameBottom + (m-i)*hy + fTop*hy; 
    UCplotPointerArray[plotRegionIndex-1]->set_frame(fL,fR,fB,fT);
    UCcontourPointerArray[plotRegionIndex-1]->set_frame(fL,fR,fB,fT); 
    UCsurfacePointerArray[plotRegionIndex-1]->set_frame(fL,fR,fB,fT);
    }
}

void  CAMgraphics::subplotOn(int m, int n)
{  
    if(plotRegionIndexBound != 1) {subplotOff();}
//
//  Create the Array of Plot Type Pointers 
//
    plotRegionIndexBound = m*n;
    plotRegionRows       = m;  
    
    UCplotPointerArray.resize(plotRegionIndexBound);
    UCcontourPointerArray.resize(plotRegionIndexBound);
    UCsurfacePointerArray.resize(plotRegionIndexBound);
    
    for(size_t i = 1; i < plotRegionIndexBound; i++)
    {
    UCplotPointerArray[i]    = new UCplot(*UCplotPointerArray[0]);
    UCcontourPointerArray[i] = new UCcontour(*UCcontourPointerArray[0]);
    UCsurfacePointerArray[i] = new UCsurface(*UCsurfacePointerArray[0]);
    }
//
//  Initialize frames for each subplot
//  
    double fLeft,fRight,fTop,fBottom;
    double hx = (frameRight - frameLeft)/double(n);
    double hy = (frameTop   - frameBottom)/double(m);
    
    int    index;
      
    for(int i = 1; i <= m; i++)
    for(int j = 1; j <= n; j++)
    {  
    index = i + (j-1)*plotRegionRows;
//
//  Frame setting for sub-plot is based on single plot frame setting
//  
    fLeft     = frameLeft   + (j-1)*hx + frameLeft*hx;
    fRight    = frameLeft   + (j-1)*hx + frameRight*hx; 
    fBottom   = frameBottom + (m-i)*hy + frameBottom*hy;
    fTop      = frameBottom + (m-i)*hy + frameTop*hy; 

    UCplotPointerArray[index-1]->set_frame(fLeft,fRight,fBottom,fTop); 
    UCcontourPointerArray[index-1]->set_frame(fLeft,fRight,fBottom,fTop);
    UCsurfacePointerArray[index-1]->set_frame(fLeft,fRight,fBottom,fTop);  
    }

    plotRegionIndex = 1;
}
void  CAMgraphics::subplotOff()
{
//
//  Delete all but the first plot instances
//
    for(int i = 1; i<= plotRegionIndexBound; i++)
    {
    delete UCplotPointerArray[i-1];
    delete UCcontourPointerArray[i-1];
    delete UCsurfacePointerArray[i-1];
    }
//
//  Reset arrays
//
    UCplotPointerArray.resize(1);
    UCcontourPointerArray.resize(1);
    UCsurfacePointerArray.resize(1);
    
//  Reset frame

    UCplotPointerArray[0]->set_frame(frameLeft,frameRight,frameBottom,frameTop);
    UCcontourPointerArray[0]->set_frame(frameLeft,frameRight,frameBottom,frameTop);
    UCsurfacePointerArray[0]->set_frame(frameLeft,frameRight,frameBottom,frameTop);

    plotRegionIndexBound = 1;
    plotRegionRows       = 1;
    plotRegionIndex      = 1;
}

void  CAMgraphics::subplot(int i, int j)
{ 
    plotRegionIndex = i + (j-1)*plotRegionRows;
}
//
//********************************************************************************
//                 TITLE AND AXIS LABEL MANIPULATION 
//********************************************************************************
//

void  CAMgraphics::drawAxis()
{ 
    (UCplotPointerArray[plotRegionIndex-1])->draw_axis();
}

void  CAMgraphics::title(const std::string& s, double size )
{
    (UCplotPointerArray[plotRegionIndex-1])->title(s,size);
    (UCcontourPointerArray[plotRegionIndex-1])->title(s,size); 
    (UCsurfacePointerArray[plotRegionIndex-1])->title(s,size);
}

void  CAMgraphics::labelX(const std::string& s, double size )
{ 
    (UCplotPointerArray[plotRegionIndex-1])->label_x(s,size);
}

void  CAMgraphics::labelY(const std::string& s, double size )
{  
    (UCplotPointerArray[plotRegionIndex-1])->label_y(s,size);
}

void  CAMgraphics::setLabelFormat(int t, int w, int p)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_label_format(t,w,p);
}

void  CAMgraphics::setLabelType(int t)
{ 
    (UCplotPointerArray[plotRegionIndex-1])->set_label_type(t);
}

void  CAMgraphics::setLabelWidth(int w)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_label_width(w);
}

void  CAMgraphics::setLabelPrecision(int p)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_label_precision(p);
}

void  CAMgraphics::setLabelCharSize(double s)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_label_char_size(s);
}

void  CAMgraphics::setTicks(int major_x,int minor_x,int major_y,int minor_y)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_ticks(major_x, minor_x, major_y, minor_y);
}

void  CAMgraphics::setXTicks(int major_x)
{
    int major, minor;
    (UCplotPointerArray[plotRegionIndex-1])->get_x_ticks(major, minor);
    (UCplotPointerArray[plotRegionIndex-1])->set_x_ticks(major_x, minor);
}

void  CAMgraphics::setYTicks(int major_y)
{
    int major, minor;
    (UCplotPointerArray[plotRegionIndex-1])->get_y_ticks(major, minor);
    (UCplotPointerArray[plotRegionIndex-1])->set_y_ticks(major_y, minor);
}

void  CAMgraphics::setXTicks(int major_x,int minor_x)
{ 
    (UCplotPointerArray[plotRegionIndex-1])->set_x_ticks(major_x, minor_x);
}

void  CAMgraphics::setYTicks(int major_y,int minor_y)
{ 
    (UCplotPointerArray[plotRegionIndex-1])->set_y_ticks(major_y, minor_y);
}


void  CAMgraphics::getTicks(int& major_x,int& minor_x,int& major_y,int& minor_y)
{
    (UCplotPointerArray[plotRegionIndex-1])->get_ticks(major_x, minor_x, major_y, minor_y);
}

void  CAMgraphics::getXTicks(int& major_x,int& minor_x)
{
    (UCplotPointerArray[plotRegionIndex-1])->get_x_ticks(major_x, minor_x);
}

void  CAMgraphics::getYTicks(int& major_y,int& minor_y)
{
    (UCplotPointerArray[plotRegionIndex-1])->get_y_ticks(major_y, minor_y);
}

void  CAMgraphics::getXTicks(int& major_x)
{
    int minor_x;
    (UCplotPointerArray[plotRegionIndex-1])->get_x_ticks(major_x, minor_x);
}

void  CAMgraphics::getYTicks(int& major_y)
{                                
    int minor_y;
    (UCplotPointerArray[plotRegionIndex-1])->get_y_ticks(major_y, minor_y);
}
//
//********************************************************************************
//              AXIS MANIPULATION MEMBER_FUNCTIONS
//********************************************************************************
//
void  CAMgraphics::axis(int auto_flag)
{ 
    (UCplotPointerArray[plotRegionIndex-1])->axis(auto_flag);
}

int  CAMgraphics::getAutoScaleFlag()
{ 
   return  (UCplotPointerArray[plotRegionIndex-1])->get_auto_scale_flag();
}

void  CAMgraphics::axis(double x_min, double x_max, double y_min, double y_max)
{
    (UCplotPointerArray[plotRegionIndex-1])->axis(x_min, x_max, y_min, y_max);
}

void  CAMgraphics::xAxisOn()

{
    (UCplotPointerArray[plotRegionIndex-1])->turn_on_x_axis();
}

void  CAMgraphics::yAxisOn()
{ 
    (UCplotPointerArray[plotRegionIndex-1])->turn_on_y_axis();
}

void  CAMgraphics::axisOn()
{
    (UCplotPointerArray[plotRegionIndex-1])->turn_on_axis();
}

void  CAMgraphics::xAxisOff()
{
    (UCplotPointerArray[plotRegionIndex-1])->turn_off_x_axis();
}

void  CAMgraphics::yAxisOff()
{
    (UCplotPointerArray[plotRegionIndex-1])->turn_off_y_axis();
}

void  CAMgraphics::axisOff()
{
    (UCplotPointerArray[plotRegionIndex-1])->turn_off_axis();
}

int CAMgraphics::getAxisFlag()
{
    return (UCplotPointerArray[plotRegionIndex-1])->get_axis_flag();
}

int CAMgraphics::getXAxisFlag()
{
    return (UCplotPointerArray[plotRegionIndex-1])->get_x_axis_flag();
}

int CAMgraphics::getYAxisFlag()
{
    return (UCplotPointerArray[plotRegionIndex-1])->get_y_axis_flag();
}

void  CAMgraphics::xLabelsOn()
{
    (UCplotPointerArray[plotRegionIndex-1])->turn_on_x_labels();
}

void  CAMgraphics::yLabelsOn()
{
    (UCplotPointerArray[plotRegionIndex-1])->turn_on_y_labels();
}

void  CAMgraphics::labelsOn()
{
    (UCplotPointerArray[plotRegionIndex-1])->turn_on_label();
}

void  CAMgraphics::xLabelsOff()
{ 
    (UCplotPointerArray[plotRegionIndex-1])->turn_off_x_labels();
}

void  CAMgraphics::yLabelsOff()
{
    (UCplotPointerArray[plotRegionIndex-1])->turn_off_y_labels();
}

void  CAMgraphics::labelsOff()
{
    (UCplotPointerArray[plotRegionIndex-1])->turn_off_label();
}

int CAMgraphics::getLabelsFlag()
{
    return (UCplotPointerArray[plotRegionIndex-1])->get_label_flag();
}

int CAMgraphics::getXLabelsFlag()
{
    return (UCplotPointerArray[plotRegionIndex-1])->get_x_label_flag();
}

int CAMgraphics::getYLabelsFlag()
{
    return (UCplotPointerArray[plotRegionIndex-1])->get_y_label_flag();
}

void  CAMgraphics::setXAxisType(int t)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_x_axis_type(t);
}

void  CAMgraphics::setYAxisType(int t)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_y_axis_type(t);
}

void  CAMgraphics::setIntercepts(double x, double y)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_intercepts(x, y);
}

void  CAMgraphics::setXIntercept(double x)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_x_intercept(x);
}

void  CAMgraphics::setYIntercept(double y)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_y_intercept(y);
}

void  CAMgraphics::setAxisColor(int c)
{    (UCplotPointerArray[plotRegionIndex-1])->set_axis_color(c);
}

void  CAMgraphics::setAxisColor(const std::vector<double>& rgb)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_axis_rgb(rgb);
}

void  CAMgraphics::setXAxisScaleType(int t)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_x_scale_type(t);
}
void  CAMgraphics::setYAxisScaleType(int t)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_y_scale_type(t);
}
int  CAMgraphics::getXAxisScaleType()
{
    return (UCplotPointerArray[plotRegionIndex-1])->get_x_scale_type();
}
int  CAMgraphics::getYAxisScaleType()
{
    return (UCplotPointerArray[plotRegionIndex-1])->get_y_scale_type();
}
//
//********************************************************************************
//    LINE AND POINT STYLE   MEMBER_FUNCTIONS
//********************************************************************************
//

void  CAMgraphics::setLineColor(int c)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_line_color(c);
}

void  CAMgraphics::setPlotLineColor(int c)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_line_color(c);
}


void  CAMgraphics::setLineColor(const std::vector<double>& rgb)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_line_rgb(rgb);
}

void  CAMgraphics::setPlotLineColor(const std::vector<double>& rgb)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_line_rgb(rgb);
}

void  CAMgraphics::setDashPattern(int d)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_dash_pattern(d);
}

void  CAMgraphics::setPlotDashPattern(int d)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_dash_pattern(d);
}

void  CAMgraphics::setUserDashPattern(int d)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_user_dash_pattern(d);
}

void  CAMgraphics::setLineWidth(double w)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_line_width(w);
}

void  CAMgraphics::setPlotLineWidth(double w)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_line_width(w);
}

void  CAMgraphics::setPointType(char p)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_point_type(p);
}


void  CAMgraphics::setPlotPointType(char p)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_point_type(p);
}

char  CAMgraphics::getPointType()
{
    return (UCplotPointerArray[plotRegionIndex-1])->get_point_type();
}

void  CAMgraphics::setPointSize(double s)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_point_size(s);
}

void  CAMgraphics::setPlotPointSize(double s)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_point_size(s);
}

void  CAMgraphics::setPointFont(const std::string& s)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_point_font(s);
}

void  CAMgraphics::setPlotPointFont(const std::string& s)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_point_font(s);
}

//
//********************************************************************************
//                PLOTTING MEMBER FUNCTIONS
//********************************************************************************
// 
/* Note p_arg goes before p_style ... */

void  CAMgraphics::drawString(double x, double y, const std::string& s, double size )
{
    (UCplotPointerArray[plotRegionIndex-1])->draw_string(x,y,s,size);
}

void  CAMgraphics::setTextColor(int c)
{    (UCplotPointerArray[plotRegionIndex-1])->set_text_color(c);
}

void  CAMgraphics::setTextColor(const std::vector<double>& rgb)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_text_rgb(rgb);
}

void  CAMgraphics::setTextAlign(double horiz, double vert)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_text_align(horiz,vert);
}

void  CAMgraphics::setPlotStyle(int s)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_plot_style(s);
}


void  CAMgraphics::setPlotLineStyle(int s)
{
    (UCplotPointerArray[plotRegionIndex-1])->set_plot_style(s);
}


int  CAMgraphics::getPlotStyle()
{
    return (UCplotPointerArray[plotRegionIndex-1])->get_plot_style();
}

void  CAMgraphics::plot()
{
    (UCplotPointerArray[plotRegionIndex-1])->plot();
}

void  CAMgraphics::plot(double *y, long n)
{
    (UCplotPointerArray[plotRegionIndex-1])->plot(y,n);
}

void  CAMgraphics::plot(double *y, long n, int p_arg)
{
    char p_arg_save = getPointType();
    (UCplotPointerArray[plotRegionIndex-1])->plot(y,n, p_arg);
    setPlotPointType(p_arg_save);
}

void  CAMgraphics::plot(double *y, long n, int p_arg, int p_style)
{
     char p_arg_save = getPointType();
     int  p_style_save = getPlotStyle();
    (UCplotPointerArray[plotRegionIndex-1])->plot(y, n, p_style, p_arg);
     setPlotPointType(p_arg_save);
     setPlotStyle(p_style_save);
}

void  CAMgraphics::plot(double *x, double *y, long n)
{ 
    (UCplotPointerArray[plotRegionIndex-1])->plot(x, y, n);
}

void  CAMgraphics::plot(double *x, double *y, long n, int p_arg)
{
     char p_arg_save = getPointType();
    (UCplotPointerArray[plotRegionIndex-1])->plot(x, y, n, p_arg);
    setPlotPointType(p_arg_save);
}

void  CAMgraphics::plot(double *x, double *y, long n, int p_arg, int p_style)
{
     char p_arg_save = getPointType();
     int  p_style_save = getPlotStyle();
    (UCplotPointerArray[plotRegionIndex-1])->plot(x, y, n, p_style, p_arg);
     setPlotPointType(p_arg_save);
     setPlotStyle(p_style_save);
}

void  CAMgraphics::plot(double (*f)(double x))
{  
    (UCplotPointerArray[plotRegionIndex-1])->plot(f);
}

void  CAMgraphics::plot(double (*f)(double x), int p_arg)
{
    char p_arg_save = getPointType();
    (UCplotPointerArray[plotRegionIndex-1])->plot(f, p_arg);
    setPlotPointType(p_arg_save);
}

void  CAMgraphics::plot(double (*f)(double x), int p_arg, int p_style)
{
     char p_arg_save = getPointType();
     int  p_style_save = getPlotStyle();
    (UCplotPointerArray[plotRegionIndex-1])->plot(f, p_style, p_arg);
     setPlotPointType(p_arg_save);
     setPlotStyle(p_style_save);
}

void  CAMgraphics::plot(double (*f)(double x), double x_min, double x_max)
{
    (UCplotPointerArray[plotRegionIndex-1])->plot(f, x_min, x_max);
}

void  CAMgraphics::plot(double (*f)(double x), double x_min, double x_max, int p_arg)
{
     char p_arg_save = getPointType();
    (UCplotPointerArray[plotRegionIndex-1])->plot(f, x_min, x_max, p_arg);
     setPlotPointType(p_arg_save);
}

void  CAMgraphics::plot(double (*f)(double x), double x_min, double x_max, int p_arg, int p_style)
{
     char p_arg_save = getPointType();
     int  p_style_save = getPlotStyle();
    (UCplotPointerArray[plotRegionIndex-1])->plot(f, x_min, x_max, p_style, p_arg);
    setPlotPointType(p_arg_save);
    setPlotStyle(p_style_save);
}

void  CAMgraphics::plot(double (*f)(double x), double x_min, double x_max, double y_min, double y_max)
{
    (UCplotPointerArray[plotRegionIndex-1])->plot(f, x_min, x_max, y_min, y_max);
}

void  CAMgraphics::plot(double (*f)(double x), double x_min, double x_max, double y_min, double y_max, int p_arg)
{
     char p_arg_save = getPointType();
    (UCplotPointerArray[plotRegionIndex-1])->plot(f, x_min, x_max, y_min, y_max, p_arg);
    setPlotPointType(p_arg_save);
}

void  CAMgraphics::plot(double (*f)(double x), double x_min, double x_max, double y_min, double y_max, int p_arg, int p_style)
{
     char p_arg_save = getPointType();
     int  p_style_save = getPlotStyle();
    (UCplotPointerArray[plotRegionIndex-1])->plot(f, x_min, x_max, y_min, y_max, p_style, p_arg);
    setPlotPointType(p_arg_save);
    setPlotStyle(p_style_save);
}


void  CAMgraphics::region(double *X, double *Y, long npoints)
{
    (UCplotPointerArray[plotRegionIndex-1])->region(X, Y, npoints);
}

void  CAMgraphics::region(double *X, double *Y, long npoints, int color, const std::vector<double>& RGB)
{
    (UCplotPointerArray[plotRegionIndex-1])->region(X, Y, npoints, color, RGB);
}
//
//********************************************************************************
//        COMBINED CONTOURING AND SURFACE PLOT MEMBER_FUNCTIONS
//********************************************************************************
// 
void  CAMgraphics::fortranArrayFlagOn()
{                                                 
    (UCcontourPointerArray[plotRegionIndex-1])->turn_on_Fortran_array_flag();
    (UCsurfacePointerArray[plotRegionIndex-1])->turn_on_Fortran_array_flag();
}

void  CAMgraphics::fortranArrayFlagOff()
{                                                 
    (UCcontourPointerArray[plotRegionIndex-1])->turn_off_Fortran_array_flag();
    (UCsurfacePointerArray[plotRegionIndex-1])->turn_off_Fortran_array_flag();
}

int  CAMgraphics::getFortranArrayFlag()
{                                                 
    return (UCcontourPointerArray[plotRegionIndex-1])->get_Fortran_array_flag();
}
//
//********************************************************************************
//                    CONTOURING MEMBER_FUNCTIONS
//********************************************************************************
//

void  CAMgraphics::contour()
{
    (UCcontourPointerArray[plotRegionIndex-1])->contour();
}

void  CAMgraphics::contour(double *data_pointer, int n, int m)
{
    (UCcontourPointerArray[plotRegionIndex-1])->contour(data_pointer, n, m);
}

void  CAMgraphics::contour(double *data_pointer, int n, int m, int n_contour)
{ 
    (UCcontourPointerArray[plotRegionIndex-1])->contour(data_pointer, n, m, n_contour);
}

void  CAMgraphics::contour(double *data_pointer, int n, int m, long n_contour)
{ 
    (UCcontourPointerArray[plotRegionIndex-1])->contour(data_pointer, n, m, int(n_contour));
}

void  CAMgraphics::contour(double *data_pointer, int n, int m, double increment)
{
    (UCcontourPointerArray[plotRegionIndex-1])->contour(data_pointer, n, m, increment);
}

void  CAMgraphics::contour(double* data_pointer, int n, int m, double low_value, double high_value)
{
    (UCcontourPointerArray[plotRegionIndex-1])->contour(data_pointer, n, m, low_value, high_value);
}

void  CAMgraphics::contour(double *data_pointer, int n, int m, int n_countour, double low_value, double high_value)
{
    (UCcontourPointerArray[plotRegionIndex-1])->contour(data_pointer, n, m, n_countour, low_value, high_value);
}

void  CAMgraphics::contour(double *data_pointer, int n, int m, long n_countour, double low_value, double high_value)
{
    (UCcontourPointerArray[plotRegionIndex-1])->contour(data_pointer, n, m, int(n_countour), low_value, high_value);
}
void  CAMgraphics::contour(double *data_pointer, int n, int m, double increment, double low_value, double high_value)
{
    (UCcontourPointerArray[plotRegionIndex-1])->contour(data_pointer, n, m, increment, low_value, high_value);
}

void  CAMgraphics::contour(double *data_pointer, int n, int m, const std::vector<double>&  contour_values, int n_contour)
{
    (UCcontourPointerArray[plotRegionIndex-1])->contour(data_pointer, n, m, contour_values, n_contour);
}

void  CAMgraphics::autoContourOn()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_on_auto_contour();
}

void  CAMgraphics::autoContourOff()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_off_auto_contour();
}

void  CAMgraphics::lineLabelsOn()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_on_line_label();
}

void  CAMgraphics::contourLineLabelsOn()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_on_line_label();
}

void  CAMgraphics::lineLabelsOff()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_off_line_label();
}

void  CAMgraphics::contourLineLabelsOff()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_off_line_label();
}

void  CAMgraphics::highLowLabelsOn()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_on_high_low_labels();
}

void  CAMgraphics::contourHighLowLabelsOn()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_on_high_low_labels();
}


void  CAMgraphics::highLowLabelsOff()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_off_high_low_labels();
}

void  CAMgraphics::contourHighLowLabelsOff()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_off_high_low_labels();
}

void  CAMgraphics::backgroundOn()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_on_background();
}

void  CAMgraphics::contourBackgroundOn()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_on_background();
}

void  CAMgraphics::backgroundOff()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_off_background();
}

void  CAMgraphics::contourBackgroundOff()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_off_background();
}

int  CAMgraphics::getBackgroundFlag()
{
    return (UCcontourPointerArray[plotRegionIndex-1])->get_background_flag();
}

void  CAMgraphics::scaledFrameOn()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_on_scaled_frame();
}

void  CAMgraphics::contourScaledFrameOn()
{
    (UCcontourPointerArray[plotRegionIndex-1])->turn_on_scaled_frame();
}

void  CAMgraphics::scaledFrameOff()
{                                                 
    (UCcontourPointerArray[plotRegionIndex-1])->turn_off_scaled_frame();
}

void  CAMgraphics::contourScaledFrameOff()
{                                                 
    (UCcontourPointerArray[plotRegionIndex-1])->turn_off_scaled_frame();
}

void  CAMgraphics::setContourLevel(long n_contour)
{                                                 
    (UCcontourPointerArray[plotRegionIndex-1])->set_contour_level(n_contour);
}

void  CAMgraphics::setContourLevel(int n_contour)
{                                                 
    (UCcontourPointerArray[plotRegionIndex-1])->set_contour_level(long(n_contour));
}

void  CAMgraphics::setContourLevel(double increment)
{                                                 
    (UCcontourPointerArray[plotRegionIndex-1])->set_contour_level(increment);
}

void  CAMgraphics::setContourLevel(float increment)
{                                                 
    (UCcontourPointerArray[plotRegionIndex-1])->set_contour_level(double(increment));
}

void  CAMgraphics::setContourLevel(double low_value, double high_value)
{                                                 
    (UCcontourPointerArray[plotRegionIndex-1])->set_contour_level(low_value, high_value);
}

void  CAMgraphics::setContourLevel(long n_contour, double low_value, double high_value)
{                                                 
    (UCcontourPointerArray[plotRegionIndex-1])->set_contour_level(n_contour, low_value,  high_value);
}

void  CAMgraphics::setContourLevel(int n_contour, double low_value, double high_value)
{                                                 
    (UCcontourPointerArray[plotRegionIndex-1])->set_contour_level(long(n_contour), low_value,  high_value);
}

void  CAMgraphics::setContourLevel(double increment, double low_value, double high_value)
{                                                 
    (UCcontourPointerArray[plotRegionIndex-1])->set_contour_level(increment, low_value, high_value);
}

void  CAMgraphics::setContourLevel(const std::vector<double>&  values, long n_contour)
{                                                 
    (UCcontourPointerArray[plotRegionIndex-1])->set_contour_level(values, n_contour);
}

void  CAMgraphics::setContourLineColor(int colorIndex)
{
    (UCcontourPointerArray[plotRegionIndex-1])->set_default_color(colorIndex);
}
//
//********************************************************************************
//                    SURFACE MEMBER_FUNCTIONS
//********************************************************************************
//
void  CAMgraphics::surface()
{ 
    (UCsurfacePointerArray[plotRegionIndex-1])->surface();
}

void  CAMgraphics::surface(double* A, long r, long c)
{
    (UCsurfacePointerArray[plotRegionIndex-1])->surface(A, r, c);
}

void  CAMgraphics::surface(double* A, long r, long c, double *x, double *y)
{
    (UCsurfacePointerArray[plotRegionIndex-1])->surface(A, r, c, x, y);
}

void  CAMgraphics::surface(double (*data)(long,long), long r, long c, double *x, double *y)
{ 
    (UCsurfacePointerArray[plotRegionIndex-1])->surface(data, r, c, x, y);
}

void  CAMgraphics::setViewPoint(double x, double y, double z)
{
    (UCsurfacePointerArray[plotRegionIndex-1])->set_view_point(x,y,z);
}

void  CAMgraphics::setSurfaceViewPoint(double x, double y, double z)
{
    (UCsurfacePointerArray[plotRegionIndex-1])->set_view_point(x,y,z);
}

void  CAMgraphics::setViewPoint(double *vp)
{ 
    (UCsurfacePointerArray[plotRegionIndex-1])->set_view_point(vp);
}

void  CAMgraphics::setFocus(double x, double y, double z)
{
    (UCsurfacePointerArray[plotRegionIndex-1])->set_focus(x,y,z);
}

void  CAMgraphics::setSurfaceFocus(double x, double y, double z)
{
    (UCsurfacePointerArray[plotRegionIndex-1])->set_focus(x,y,z);
}

void  CAMgraphics::setFocus(double *f)
{  
    (UCsurfacePointerArray[plotRegionIndex-1])->set_focus(f);
}

void  CAMgraphics::setScaleFactor(double sf)
{
    (UCsurfacePointerArray[plotRegionIndex-1])->set_scale_factor(sf);
}

void  CAMgraphics::setSurfaceScaleFactor(double sf)
{
    (UCsurfacePointerArray[plotRegionIndex-1])->set_scale_factor(sf);
}

void  CAMgraphics::setXOffset(double xo)
{
    (UCsurfacePointerArray[plotRegionIndex-1])->set_xoffset(xo);
}

void  CAMgraphics::setYOffset(double yo)
{
    (UCsurfacePointerArray[plotRegionIndex-1])->set_yoffset(yo);
}
//
//******************************************************************************
//                        GRAPHICS STATE MANIPULATIOIN
//******************************************************************************
/*
void CAMgraphics::setState(const CAMgraphicsState& S)
{
    initialize();
//
//  Allocate and Copy
//
    if(S.plotRegionIndexBound > 0)
    {
    UCplotPointerArray.resize(S.plotRegionIndexBound);
    UCcontourPointerArray.resize(S.plotRegionIndexBound);
    UCsurfacePointerArray.resize(S.plotRegionIndexBound);

    for(int i = 0; i < S.plotRegionIndexBound; i++)
    {
    UCplotPointerArray[i]    = S.UCplotPointerArray[i];
    UCcontourPointerArray[i] = S.UCcontourPointerArray[i];
    UCsurfacePointerArray[i] = S.UCsurfacePointerArray[i];
    }

    frameLeft             = S.frameLeft;
    frameRight            = S.frameRight;
    frameBottom           = S.frameBottom;
    frameTop              = S.frameTop;
    plotRegionIndexBound  = S.plotRegionIndexBound;
    plotRegionIndex       = S.plotRegionIndex;
    plotRegionRows        = S.plotRegionRows;
    defaultDriverFlag     = S.defaultDriverFlag;
    OutputDeviceDriver    = S.OutputDeviceDriver;
    }
}
void CAMgraphics::getState(CAMgraphicsState& S)
{
//
//  delete S entries
//
    if(S.plotRegionIndexBound > 0)
    {
      delete [] S.UCplotPointerArray;
      delete [] S.UCcontourPointerArray;
      delete [] S.UCsurfacePointerArray;

      S.frameLeft             = 0.0;
      S.frameRight            = 0.0;
      S.frameBottom           = 0.0;
      S.frameTop              = 0.0;
      S.plotRegionIndex       = 0;
      S.plotRegionRows        = 0;
      S.defaultDriverFlag     = 0;
      S.OutputDeviceDriver    = 0;
    }
    S.plotRegionIndexBound  = 0;
//
//  Allocate and Copy
//
    if(plotRegionIndexBound > 0)
    {
    S.UCplotPointerArray    = new UCplot*[plotRegionIndexBound];
    S.UCcontourPointerArray = new UCcontour*[plotRegionIndexBound];
    S.UCsurfacePointerArray = new UCsurface*[plotRegionIndexBound];
    for(int i = 0; i < plotRegionIndexBound; i++)
    {
    S.UCplotPointerArray[i]    = UCplotPointerArray[i];
    S.UCcontourPointerArray[i] = UCcontourPointerArray[i];
    S.UCsurfacePointerArray[i] = UCsurfacePointerArray[i];
    }
    S.frameLeft             = frameLeft;
    S.frameRight            = frameRight;
    S.frameBottom           = frameBottom;
    S.frameTop              = frameTop;
    S.plotRegionIndexBound  = plotRegionIndexBound;
    S.plotRegionIndex       = plotRegionIndex ;
    S.plotRegionRows        = plotRegionRows;
    S.defaultDriverFlag     = defaultDriverFlag;
    S.OutputDeviceDriver    = OutputDeviceDriver;
    }
}
*/

//
//********************************************************************************
//                     CPP File End 
//********************************************************************************
//

 
