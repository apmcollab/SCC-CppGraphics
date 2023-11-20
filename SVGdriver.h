//
//******************************************************************************
//                              SVGdriver.H
//******************************************************************************
// 
//                  HEADER FILE FOR CLASS SVGdriver
//
//********************************************************************************
//
//            Initial Version             : Chris Anderson 
//
//                            (C) UCLA 2023
//********************************************************************************
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
#include "ucdriver.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include <vector>

#include "HersheyFont.h"

#ifndef SVG_DRIVER_
#define SVG_DRIVER_

#define HERSHEY_LINE_WIDTH  0.001
#define HERSHEY_FONT  "HersheySerif"
#define HERSHEY_FONT_SIZE .002


// Default plot area is

#define HERSHEY_PAGE_WIDTH    8.5  // inches
#define HERSHEY_PAGE_HEIGHT   11.0 // inches
#define HERSHEY_PAGE_MARGIN   1.0  // inches
#define HERSHEY_PAGE_DPI      300
#define HERSHEY_FILENAME      "graph"


class SVGdriver : public UCdriver
{
public:

	long               pageCount;
    bool                pageOpen;
    bool       multipleFrameFlag;

	std::stringstream       page;
	std::stringstream pageHeader;

    double            xCoordSize;
	double            yCoordSize;
	double           xyCoordSize;
	double            marginSize;

	double pageWidth;
	double pageHeight;
	double pageMargin;
	long   pageDPI;

	std::string               fileName;
	std::string         rgbColorString;
	std::string             dashString;

	int backgroundColor;

	SVGdriver() : UCdriver()
	{
	initialize(HERSHEY_FILENAME,HERSHEY_PAGE_WIDTH,HERSHEY_PAGE_HEIGHT,HERSHEY_PAGE_DPI,HERSHEY_PAGE_MARGIN,UCdriver::NONE,true);
    }


    SVGdriver(const std::string& fileName, bool multipleFrameFlag = true) : UCdriver(fileName)
    {
    initialize(fileName,HERSHEY_PAGE_WIDTH,HERSHEY_PAGE_HEIGHT,HERSHEY_PAGE_DPI,HERSHEY_PAGE_MARGIN,UCdriver::NONE,multipleFrameFlag);
    }


    SVGdriver(const std::string& fileName, double pageWidth, double pageHeight,
    double pageMargin, long pageDPI, int backgroundColor, bool  multipleFrameFlag) : UCdriver(fileName)
    {
    initialize(fileName,pageWidth,pageHeight,pageMargin,pageDPI,backgroundColor, multipleFrameFlag);
    }

    ~SVGdriver(){}

    void initialize(const std::string& fileName,double pageWidth, double pageHeight, double pageMargin, long pageDPI,
    int backgroundColor, bool multipleFrameFlag)
    {

    	this->pageWidth  = pageWidth;
    	this->pageHeight = pageHeight;
		this->pageMargin = pageMargin;
		this->pageDPI    = pageDPI;


    	this->fileName          = fileName;
    	this->backgroundColor   = backgroundColor;
    	this->multipleFrameFlag = multipleFrameFlag;


    	marginSize = pageDPI*pageMargin;

    	page.clear();
    	pageCount = 0;
    	pageOpen = true;

    	page << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
    	page << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
    	page << "<svg width = \"" << std::to_string(pageWidth) << "in\" " <<  " height = \"" << std::to_string(pageHeight) << "in\" ";
    	page << " viewBox=\"" << 0 << " " << 0 << " " << pageDPI*pageWidth  << " " << pageDPI*pageHeight << "\"" << " xmlns=\"http://www.w3.org/2000/svg\">\n";


        xCoordSize  = pageDPI*pageWidth  - 2*marginSize;
    	yCoordSize  = pageDPI*pageHeight - 2*marginSize;
    	xyCoordSize = xCoordSize;



    	std::vector<double> RGB = {255.0,255.0,255.0};
    	if(backgroundColor != UCdriver::NONE)
    	{
        setRGBcolorValue(backgroundColor,RGB,rgbColorString);
        page << "<rect x=\"0\" y=\"0\" width=\"" << pageDPI*pageWidth << "\" height=\"" << pageDPI*pageHeight << "\"\n";
        page << "fill= " << rgbColorString << " stroke= " << rgbColorString << " stroke-width=\"8\" /> \n";
    	}
    	else
    	{}

        // Capture page header for multiple frame output

        pageHeader.clear();
    	pageHeader << page.str();



        //page << "<rect x=\""<< marginSize << "\" y=\"" << marginSize << "\" width=\"" << xCoordSize << "\" height=\"" << xCoordSize<< "\"\n";
        //page << "fill=\"white\" stroke=\"red\" stroke-width=\"8\" /> \n";
    }

    void lines(double *x, double *y, long npoints, int dash_pattern,
    unsigned user_pattern, double width, int iColor, const std::vector<double>& RGB)
    {
        pageOpen = true;

    	setRGBcolorValue(iColor,RGB,rgbColorString);
    	if(width < HERSHEY_LINE_WIDTH) {width = HERSHEY_LINE_WIDTH;}

    	int lineWidth = std::ceil(width*xyCoordSize);
    	if(lineWidth < 1) {lineWidth = 1;};

    	setDashValue(dash_pattern, user_pattern,lineWidth, dashString);

    	page << "<polyline fill=\"none\" points = \"";
    	for(long k = 0; k < npoints; k++)
    	{
    	page << marginSize + x[k]*xyCoordSize << "," << marginSize + (xyCoordSize - y[k]*xyCoordSize) << " ";
    	}
    	page << "\" ";
    	page << " stroke=" + rgbColorString + " stroke-width=\"" << lineWidth << "\" ";

    	if(dashString.empty())
    	{
    	page << " /> \n";
    	}
    	else
    	{
    	page << dashString << " /> \n";
    	}

    }



    void line(double x1, double y1, double x2, double y2,
            int dash_pattern, unsigned user_pattern, double width,
            int iColor, const std::vector<double>& RGB)
    {
        pageOpen = true;

    	setRGBcolorValue(iColor,RGB,rgbColorString);

    	if(width < HERSHEY_LINE_WIDTH) {width = HERSHEY_LINE_WIDTH;}


    	int lineWidth = std::ceil(width*xyCoordSize);
    	if(lineWidth < 1) {lineWidth = 1;};


    	setDashValue(dash_pattern, user_pattern,lineWidth, dashString);

        x1 *= xyCoordSize;
        y1 *= xyCoordSize;

        x2 *= xyCoordSize;
        y2 *= xyCoordSize;

        x1 += marginSize;
        x2 += marginSize;
        y1 = marginSize + (xyCoordSize - y1);
        y2 = marginSize + (xyCoordSize - y2);

    	page << "<line x1=\""<< x1 << "\" y1=\"" << y1 << "\"" << " x2=\""<< x2 << "\" y2=\"" << y2 << "\" ";
    	page << " stroke=" + rgbColorString + " stroke-width=\"" << lineWidth << "\" ";

    	if(dashString.empty())
    	{
    	page << " /> \n";
    	}
    	else
    	{
    	page << dashString << " /> \n";
    	}
    }


void point(double x,double y, char chr, const std::string& font,double size, int color, const std::vector<double>& rgb)
{
    pageOpen = true;

    std::string s;
    s.push_back(chr);
    double horiz_just = 0.0;
    double vert_just  = 0.0;
    double rotation   = 0.0;

    plotHersheyText(x,y, s, font, size,rotation,horiz_just,vert_just, color,rgb);
};
void points(double *X,double *Y,long npoints, char chr,const std::string& font, double size, int color,const std::vector<double>& rgb)
{
    pageOpen = true;

    std::string s;
    s.push_back(chr);
    double horiz_just = 0.0;
    double vert_just  = 0.0;
    double rotation   = 0.0;

    long k;
    for(k = 0; k < npoints; k++)
    {
    plotHersheyText(X[k],Y[k], s, font, size,rotation,horiz_just,
    vert_just, color,rgb);
    }
}

void text(double x,double y,const std::string& s,const std::string&  font,double size,double rotation,
		double horiz_just,double vert_just,
		int color,const std::vector<double>& rgb)
{
    pageOpen = true;

    plotHersheyText(x,y, s, font, size,rotation,horiz_just,vert_just, color,rgb);
}


//##################################################################################
//                       PixelDriver::plotHersheyText
//##################################################################################
//
void plotHersheyText(double x, double y, const std::string& s,const std::string& font, double size,
double rotation, double horiz_just, double vert_just, int color, const std::vector<double>& rgb)
{
    long i; long j;

    HersheyFont Hf;
//
//   Select Font
//
    if(not font.empty())
    {
    Hf.setFont(font);
    }

    double textScale;        // fractional size of text
    double hersheyHeight;    // height of font in Hershey plotting units
    double hersheyWidth;     // width of string in Hershey plotting units
    double alpha;            // scale factor between Hershey and [0,1]x[0,1] units

    double xCorner;
    double yCorner;

    if(std::abs(size) <= HERSHEY_FONT_SIZE) {size = HERSHEY_FONT_SIZE;}
    textScale     = size;

    hersheyHeight = Hf.getHersheyHeight();
    hersheyWidth  = Hf.getHersheyWidth(s);

    alpha     = textScale/hersheyHeight;

    xCorner    = (-0.5 - .5*(horiz_just))*hersheyWidth;
    yCorner    = (-0.5 - .5*(vert_just))*hersheyHeight;
//
//  Draw the text
//
    double           xS, yS;
    double            theta;
    double          xt,xtmp;
    double          yt,ytmp;

    long          charCount;
    char*         glyphCode;

    double xCharPlot[300];
    double yCharPlot[300];

    double  xInit, xFinal;
    double xStart, xEnd;
    double xWidth;
    int    stringSize;

    int dash_pattern      = 0;
    unsigned user_pattern = 0;
    double width          = 0;


    xEnd      = xCorner;
    theta     = (rotation/180.0)*3.14159265359;

    for(i = 0; i < (long)s.size(); i++)
    {
    glyphCode  = Hf.getGlyphCodeString(s[i]);
    stringSize = strlen(glyphCode);

    if(stringSize != 0)
    {
    charCount   = 0;
    xInit  = int(glyphCode[0])    - 82;
    xFinal = int(glyphCode[1])    - 82;
    xStart = xEnd   - xInit;
    xWidth = xFinal - xInit;

    for(j = 1; j < stringSize/2; j++)
    {
    xS = int(glyphCode[2*j])    - 82;
    yS = 82 - int(glyphCode[2*j +1]);

        // Invert y since I'm plotting in a Cartesian coordinate
        // system.

        if((xS == -50)&&(yS == 0))
        {
         lines(xCharPlot, yCharPlot, charCount, dash_pattern, user_pattern, width, color, rgb);
         charCount = 0;
        }
        else if (j == (stringSize/2)-1)
        {
         xtmp = alpha*double(xS) +   alpha*(xStart);
         ytmp = alpha*double(yS) +   alpha*(yCorner)
              - alpha*(HersheyFont::HERSHEY_BOTTOMLINE);

         xt   = cos(theta)*xtmp - sin(theta)*ytmp;
         yt   = sin(theta)*xtmp + cos(theta)*ytmp;

         xCharPlot[charCount] =  x + xt;
         yCharPlot[charCount] =  y + yt;
         charCount++;

         lines(xCharPlot, yCharPlot, charCount, dash_pattern, user_pattern, width, color, rgb);
         charCount = 0;
        }
        else
        {
         xtmp = alpha*double(xS) +   alpha*(xStart);
         ytmp = alpha*double(yS) +   alpha*(yCorner)
              - alpha*(HersheyFont::HERSHEY_BOTTOMLINE);

         xt   = cos(theta)*xtmp - sin(theta)*ytmp;
         yt   = sin(theta)*xtmp + cos(theta)*ytmp;

         xCharPlot[charCount] =  x + xt;
         yCharPlot[charCount] =  y + yt;
         charCount++;
        }
    }
    xEnd      += xWidth;
    }
    }
}


    /*
    void point(double x, double y, char p, const std::string& font, double size,
             int color, const std::vector<double>& RGB)
    {}

    void points(double *X, double *Y, long np, char p, const std::string& font,
              double size, int color, const std::vector<double>& RGB)
    {}

    void text(double x, double y, const std::string& s, const std::string& font, double size,
            double rotation, double horiz_just, double vert_just,
            int color, const std::vector<double>& RGB){}
    */
    void region(double *x, double *y, long npoints, int iColor, const std::vector<double>& RGB)
    {
        pageOpen = true;
    	setRGBcolorValue(iColor,RGB,rgbColorString);
    	int lineWidth = 1;

    	page << "<polyline fill= " << rgbColorString << " points = \"";
    	for(long k = 0; k < npoints; k++)
    	{
    	page << marginSize + x[k]*xyCoordSize << "," << marginSize + (xyCoordSize - y[k]*xyCoordSize) << " ";
    	}
    	page << "\" ";
    	page << " stroke=" + rgbColorString + " stroke-width=\"" << lineWidth << "\" ";
    	page << " /> \n";
    }

    void frame()
    {
    output();
    page.str("");
    pageCount++;
    page << pageHeader.str();
    }
    void output()
    {

    	std::ofstream fout;
    	std::string outputName = fileName;
    	if(pageOpen)
    	{
    	    if((multipleFrameFlag)||(pageCount > 0))
    	    {
    	    outputName = fileName + "_" + std::to_string(pageCount) + ".svg";
    	    }
    	    else
    	    {
    	    outputName = fileName + ".svg";
    	    }

    		fout.open(outputName);
    		page << "</svg>\n";
    		//std::cout << page.str() << std::endl;
    		fout << page.str() << std::endl;
        	fout.close();
        	page.clear();
        	pageOpen = false;
    	}

    }


    void setDashValue(int dash_pattern, unsigned user_pattern,long lineWidth, std::string& dashString)
    {
    dashString.clear();

    if((dash_pattern == 0)||(dash_pattern == UCdriver::SOLID))
    {
    return;
    }

    dashString = "stroke-dasharray=\"";
    switch(dash_pattern)
    {
    case UCdriver::DASH               : dashString   += std::to_string(4*lineWidth) + " " + std::to_string(lineWidth); break;
    case UCdriver::DOUBLE_DASH        : dashString   += std::to_string(8*lineWidth) + " " + std::to_string(lineWidth); break;
    case UCdriver::DASH_DOT           : dashString   +=
                                        std::to_string(4*lineWidth) + " " +
                                        std::to_string(lineWidth)   + " " +
                                        std::to_string(lineWidth)   + " " +
                                        std::to_string(lineWidth); break;
    case UCdriver::DASH_DOUBLE_DOT    : dashString   +=
                                        std::to_string(4*lineWidth) + " " +
                                        std::to_string(lineWidth)   + " " +
                                        std::to_string(lineWidth)   + " " +
                                        std::to_string(lineWidth)   + " " +
                                        std::to_string(lineWidth)   + " " +
                                        std::to_string(lineWidth); break;
    case UCdriver::DOTS               : dashString   += std::to_string(lineWidth); break;
    case UCdriver::USER_DASH          : dashString.clear(); break; // USER_DASH not being defined
    }

    dashString += "\" ";
    }

    void setRGBcolorValue(int iColor,const std::vector<double>& rgb, std::string& rgbColorString)
    {

    std::vector<int> rgbColorValue(3,0);

    switch(iColor)
    {
    case UCdriver::BLACK         : rgbColorValue = {0,0,0};       break;
    case UCdriver::DARK_GREY     : rgbColorValue = {128,128,128}; break;
    case UCdriver::LIGHT_GREY    : rgbColorValue = {192,192,192}; break;
    case UCdriver::BLUE          : rgbColorValue = {0,0,255};     break;
    case UCdriver::LIGHT_BLUE    : rgbColorValue = {130,130,255}; break;
    case UCdriver::GREEN         : rgbColorValue = {0,255,0};     break;
    case UCdriver::LIGHT_GREEN   : rgbColorValue = {192,192,192}; break;
    case UCdriver::CYAN          : rgbColorValue = {0,255,255};   break;
    case UCdriver::LIGHT_CYAN    : rgbColorValue = {128,255,255}; break;
    case UCdriver::RED           : rgbColorValue = {255,0,0};     break;
    case UCdriver::MAGENTA       : rgbColorValue = {255,0,255};   break;
    case UCdriver::LIGHT_MAGENTA : rgbColorValue = {255,128,255}; break;
    case UCdriver::ORANGE        : rgbColorValue = {255,128,64};  break;
    case UCdriver::YELLOW        : rgbColorValue = {255,255,0};   break;
    case UCdriver::WHITE         : rgbColorValue = {255,255,255}; break;
    case UCdriver::USER_RGB      : rgbColorValue[0] = rgb[0]; rgbColorValue[1] = rgb[1]; rgbColorValue[2] = rgb[2]; break;
    default : rgbColorValue = {0,0,0};
    }

   rgbColorString.clear();
   rgbColorString  = "\"rgb(";
   rgbColorString += std::to_string(rgbColorValue[0]) + ",";
   rgbColorString += std::to_string(rgbColorValue[1]) + ",";
   rgbColorString += std::to_string(rgbColorValue[2]) + ")\"";
}
};
#endif
 
