#include "CAMsvgDriver.h"

#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#include "CAMplotArguments.h"
#include "CAMregionArguments.h"
#include "CAMcontourArguments.h"
#include "CAMsurfaceArguments.h"
#include "CAMtextArguments.h"
#include "CAMsetArguments.h"
#include "ucdriver.h"
#include "camgraph.h"


//######################################################################
//
//            Chris Anderson (C) UCLA
//
//                 Nov. 12, 2023
//
//######################################################################
//
//
/*
#############################################################################
#
# Copyright  2023- Chris Anderson
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

// The constructor creates a GraphicsProcess and a GraphicsState
// the driver is not created until an open(...) member function
// is called. This allows the same settings for graphical output to
// be applied to multiple output files.
//

CAMsvgDriver::CAMsvgDriver()
{
	S          = nullptr;
    G          = nullptr;
    svgDriver  = nullptr;
    initialize();
} 

void CAMsvgDriver::initialize()
{
    if(S         != nullptr) {delete S;}
    if(G         != nullptr) {delete G;}
	if(svgDriver != nullptr) {delete svgDriver;}
	
    S = new CAMgraphicsState();
    G = new CAMgraphics;
    
    dTypeName  = "CAMsvdDriver";
    outputFilePrefix.clear();
}


CAMsvgDriver::~CAMsvgDriver()
{
    if(S != nullptr)         {delete S;}
    if(G != nullptr)         {delete G;}
	if(svgDriver != nullptr) {delete svgDriver;}
}                                            

void CAMsvgDriver::open()
{
	std::string fileName = "graph";
	bool letterSize      = true;
	open(fileName,letterSize);
}

//
// Open creates and attaches a SVG low level driver that outputs
// to the file [fileNamePrefix].cif
// 
//
// Convenience initialization
//
void CAMsvgDriver::open(const std::string& fileNamePrefix, bool letterSize)
{
    outputFilePrefix = fileNamePrefix;
    
    double pageWidth;
	double pageHeight;
	long   pageDPI;
	double pageMargin ;

	if(letterSize)
	{
    pageWidth  =   8.5;
	pageHeight =  11.0;
	pageDPI    =   600;
	pageMargin =   1.0;
	}
	else
	{
	pageWidth  =   6.0;
	pageHeight =   6.0;
	pageDPI    =   600;
	pageMargin =   0.0;
	}

	bool multipleFrameFlag = true;
	int  backgroundColor   = UCdriver::NONE;

	if(svgDriver != nullptr) {delete svgDriver;}

    svgDriver = new SVGdriver(outputFilePrefix,pageWidth, pageHeight,pageMargin,pageDPI,backgroundColor,multipleFrameFlag);

	G->open(svgDriver);
    G->getState(*S);
}


void CAMsvgDriver::open(const std::string& fileNamePrefix, double pageWidth, double pageHeight, double pageMargin, long pageDPI,
int backgroundColor, bool multipleFrameFlag)
{
    outputFilePrefix = fileNamePrefix;

	if(svgDriver != nullptr) {delete svgDriver;}
	
	svgDriver = new SVGdriver(outputFilePrefix,pageWidth, pageHeight,pageMargin,pageDPI,backgroundColor,multipleFrameFlag);

	G->open(svgDriver);
    G->getState(*S);
}

void CAMsvgDriver::close()
{
    G->setState(*S);
    G->close();
    if(svgDriver != nullptr) {delete svgDriver;}
}

void CAMsvgDriver::frame()
{
	G->setState(*S);
    G->frame();
}


void CAMsvgDriver::accept(const CAMplotArguments& A)
{
	G->setState(*S);
//
// Unpack arguments
//
	int callType            = int(A.callType);

	long   n                 = A.n;
	long   s                 = A.s;
	char   c                 = A.c;

	double* x                = A.x;
	double* y                = A.y;

	switch(callType)
	{
	case 0  : G->plot(); break;
	case 1  : G->plot(y,n); break;
	case 2  : G->plot(y,n,c); break;
	case 3  : G->plot(y,n,c,s); break;
	case 11 : G->plot(x,y,n); break;
	case 12 : G->plot(x,y,n,c); break;
	case 13 : G->plot(x,y,n,c,s); break;
	}

	G->getState(*S);
}

void CAMsvgDriver::accept(const CAMcontourArguments& A)
{
	G->setState(*S);
//
// Unpack arguments
//
	int callType            = int(A.callType);

	long   m                 = A.m;
	long   n                 = A.n;

	long   n_c               = A.n_c;
	double c_min             = A.c_min;
	double c_max             = A.c_max;
	double c_inc             = A.c_inc;

	double* z                      = A.z;
	std::vector<double> c_values   = A.c_values;

	int  colorIndex                  = A.defaultColor;

	switch(callType)
	{
	case 0  : G->contour(); break;
	case 1  : G->contour(z,m,n); break;
	case 2  : G->contour(z,m,n,n_c); break;
	case 3  : G->contour(z,m,n,c_inc); break;
	case 4  : G->contour(z,m,n,c_min, c_max); break;
	case 5  : G->contour(z,m,n,n_c,c_min, c_max); break;
	case 6  : G->contour(z,m,n,c_inc,c_min, c_max); break;
	case 7  : G->contour(z,m,n,c_values, n_c); break;
	case 8  : G->setContourLineColor(colorIndex); break;
  }

  G->getState(*S);
}

void CAMsvgDriver::accept(const CAMsurfaceArguments& A)
{
	G->setState(*S);
    int callType            = int(A.callType);

  	long   m                 = A.m;
  	long   n                 = A.n;

  	double* z                = A.z;
  	double* x                = A.x;
  	double* y                = A.y;

  	switch(callType)
  	{
  	case 0  : G->surface(); break;
  	case 1  : G->surface(z,m,n); break;
  	case 2  : G->surface(z,m,n,x,y); break;
  	}

	G->getState(*S);
}

void CAMsvgDriver::accept(const CAMtextArguments& A)
{
	G->setState(*S);

  	int callType            = int(A.callType);

  	double      x             = A.x;
  	double      y             = A.y;
  	double      size          = A.size;
  	std::string St            = A.s;

  
  	switch(callType)
  	{
  	case 1  : if(size <= 0.0) {CAMgraphics::drawString(x,y,St);}
           	  else            {G->drawString(x,y,St,size);} break;
  	case 2  : if(size <= 0.0) {G->title(St);}
           	  else            {G->title(St,size); }break;
  	case 3  : if(size <= 0.0) {G->labelX(St);}
              else            {G->labelX(St,size);} break;
  	case 4  : if(size <= 0.0) {G->labelY(St);}
           	  else            {G->labelY(St,size);} break;
 	 }
	G->getState(*S);
}

void CAMsvgDriver::accept(const CAMregionArguments& A)
{
	G->setState(*S);
//
// Unpack arguments
//
	int callType            = int(A.callType);

	long   n                = A.n;
	int   col               = A.col;
	std::vector<double> rgb = A.rgb;

	double* x                = A.x;
	double* y                = A.y;

	switch(callType)
	{
	case 0  : G->region(x,y,n); break;
	case 1  : G->region(x,y,n,col,rgb); break;
	}

	G->getState(*S);
}

void CAMsvgDriver::accept(const CAMsetArguments& A)
{
	G->setState(*S);
//
// Unpack arguments
//

  	int callType            = int(A.callType);


  	std::vector<long>  I    = A.i;
  	std::vector<double> D   = A.d;
    std::string  St         = A.b;

 	 switch(callType)
 	{
//
// Frame and Subplot
//
  	case 10  : G->setFrame(D[0],D[1],D[2],D[3]); break;
  	case 11  : G->subplotOn(I[0],I[1])         ; break;
    case 12  : G->subplot(I[0],I[1])           ; break;
  	case 13  : G->subplotOff()                 ; break;
//
// Axis Range and Scaling Manipulation
//
    case 21  : G->axisAutoScaleOn()                ; break;
    case 22  : G->axisAutoScaleOn()                ; break;
    case 23  : G->setAxisRange(D[0],D[1],D[2],D[3]); break;
//
// Axis Commands
//
    case 24  : G->drawAxis()                       ; break;
    case 25  : G->setTicks(I[0],I[1],I[2],I[3])    ; break;
    case 26  : G->setXTicks(I[0],I[1])             ; break;
    case 27  : G->setYTicks(I[0],I[1])             ; break;

    case 28  : G->xAxisOn()                          ; break;
    case 29  : G->xAxisOff()                         ; break;
    case 30  : G->yAxisOn()                          ; break;
    case 31  : G->yAxisOff()                         ; break;
    case 32  : G->axisOn()                           ; break;
    case 33  : G->axisOff()                          ; break;
    case 34  : G->xLabelsOn()                        ; break;
    case 35  : G->xLabelsOff()                       ; break;
    case 36  : G->yLabelsOn()                        ; break;
    case 37  : G->yLabelsOff()                       ; break;
    case 38  : G->labelsOn()                         ; break;
    case 39  : G->labelsOff()                        ; break;

    case 40  : G->setXAxisType(I[0])                 ; break;
    case 41  : G->setYAxisType(I[0])                 ; break;
    case 42  : G->setIntercepts(D[0],D[1])           ; break;
    case 43  : G->setXIntercept(D[0])                ; break;
    case 44  : G->setYIntercept(D[0])                ; break;
    case 45  : G->setAxisColor(I[0])                 ; break;
    case 46  : G->setAxisColor(D)                    ; break;

    case 47  : G->setLabelType(I[0])                 ; break;
    case 48  : G->setLabelWidth(I[0])                ; break;
    case 49  : G->setLabelPrecision(I[0])            ; break;
    case 50  : G->setLabelCharSize(D[0])             ; break;
    case 51  : G->setLabelFormat(I[0],I[1],I[2])     ; break;

    case 71  : G->setPlotStyle(I[0]);                ; break;
    case 72  : G->setLineColor(I[0]);                ; break;
    case 73  : G->setLineColor(D);                   ; break;
    case 74  : G->setDashPattern(I[0]);              ; break;

    case 75  : G->setLineWidth(D[0]);                ; break;
    case 76  : G->setPointType(St[0]);                ; break;
    case 77  : G->setPointSize(D[0]);                ; break;
    case 78  : G->setPointFont(St);                   ; break;


    case 91  : G->setContourLevel(I[0])              ; break;
    case 92  : G->setContourLevel(D[0])              ; break;
    case 93  : G->setContourLevel(D[0],D[1])         ; break;
    case 94  : G->setContourLevel(I[0],D[0],D[1])    ; break;

    case 95  : G->setContourLevel(D[0],D[1],D[2])    ; break;
    case 96  : G->setContourLevel(D,I[0])            ; break;
  
    case 97  : G->autoContourOn()                    ; break;
    case 98  : G->autoContourOff()                   ; break;

  	 case 99  : G->lineLabelsOn()                     ; break;
  	 case 100 : G->lineLabelsOff()                    ; break;
  	 case 101 : G->highLowLabelsOn()                  ; break;
  	 case 102 : G->highLowLabelsOff()                 ; break;

    case 103 : G->backgroundOn()                     ; break;
    case 104 : G->backgroundOff()                    ; break;
    case 105 : G->scaledFrameOn()                    ; break;
    case 106 : G->scaledFrameOff()                   ; break;

  	case 121  : G->setViewPoint(D[0],D[1],D[2])      ; break;
    case 122  : G->setFocus(D[0],D[1],D[2])          ; break;
    case 123  : G->setScaleFactor(D[0])              ; break;

    case 145  : G->setTextColor(I[0])                 ; break;
    case 146  : G->setTextColor(D)                    ; break;
    case 147  : G->setTextAlign(D[0],D[1])            ; break;
  }

	G->getState(*S);
}



 
