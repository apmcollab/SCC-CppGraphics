#ifndef CAM_SVD_DRIVER_
#define CAM_SVD_DRIVER_
//
//######################################################################
//
//            Chris Anderson (C) UCLA
//
//                 Nov. 12, 2023
//
//######################################################################
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
#include <string>
#include "CAMgraphicsDriver.h"
#include "SVGdriver.h"


#ifndef CAMPLOTARGUMENTS__
class CAMplotArguments;
#endif

#ifndef CAM_REGION_ARGUMENTS__
class CAMregionArguments;
#endif

#ifndef CAMCONTOURARGUMENTS__
class CAMcontourArguments;
#endif

#ifndef CAMSURFACEARGUMENTS__
class CAMsurfaceArguments;
#endif

#ifndef CAMTEXTARGUMENTS__
class CAMtextArguments;
#endif

#ifndef CAMSETARGUMENTS__
class CAMsetArguments;
#endif

#ifndef CAMGRAPHICS_
class CAMgraphicsState;
class CAMgraphics;
#endif

class CAMsvgDriver : public CAMgraphicsDriver
{

public  :

	CAMsvgDriver();
    CAMsvgDriver(const std::string& outputFileName,bool letterSize = false);
    CAMsvgDriver(const std::string& fileName,double pageWidth, double pageHeight, double pageMargin,
    long pageDPI,int backgroundColor, bool multipleFrameFlag);

    virtual ~CAMsvgDriver();
    
	void open(bool letterSize = false);

	void open(const std::string& fileName,double pageWidth, double pageHeight, double pageMargin, long pageDPI,
	int backgroundColor, bool multipleFrameFlag);

	void close();
	void frame();
	void accept(const CAMplotArguments& A);
	void accept(const CAMregionArguments& A);
	void accept(const CAMcontourArguments& A);
	void accept(const CAMsurfaceArguments& A);
	void accept(const CAMtextArguments& A);
 	void accept(const CAMsetArguments& A);

 	SVGdriver* getDriver()
 	{return svgDriver;}


private :

   CAMgraphics* G;
   CAMgraphicsState* S;
   std::string outputFile;
   SVGdriver*   svgDriver;

};
#endif 
