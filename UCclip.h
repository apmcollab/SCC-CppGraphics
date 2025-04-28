//
//******************************************************************************
//                              UCCLIP.H
//******************************************************************************
//
//                    HEADER FILE FOR CLASS UCclip 
//
//********************************************************************************
//            Chris Anderson                (C) UCLA 2003
//
//           
// Source Construction Date : 01/03/03 
//                           
// A class of static utility functions for implementing "smart" line clipping
//       
//********************************************************************************
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
#include <cmath>

#ifndef UCclip_
#define UCclip_

class UCclip
{

public : 
//
// This routine determines the number of points that need to
// be plotted when "smart" clipping is done. This routine is called before
// to determine the size of the xClip and yClip arrays used as arguments to the 
// getClippledPoints(...) member function.
//
static long getClippedPlotPointCount(double* xP, double* yP, long n, double xMin,
double xMax, double yMin, double yMax);

//
// createClippedPoints(...) creates entries in the arrays xClip and yClip that are 
// the coordinates of the clipped polyline whose coordinates are specified in the
// arrays xP and yP. xClip and yClip must be allocated externally to this routine,
// and have a size that is greater than the value returned by the 
// getClippedPlotPointCount(...) member function. 
//
//
static void createClippedPoints(double* xClip,double* yClip, double* xP, double*yP, 
long n, double xMin, double xMax, double yMin, double yMax);

//
// This routine determines the horizontal and vertical projection 
// of the point (x,y) onto the boundary of the region [xMin,xMax]x[yMin,yMax]
//
static void getBoundaryProjection(double& xProj, double& yProj, double x, double y,
double xMin, double xMax, double yMin, double yMax);

//
// This routine determines if the point (x,y) is in the region
// [xMin,xMax] x [yMin,yMax]
//
static int inRegion(double x, double y, double xMin, double xMax, 
double yMin, double yMax);

//
// This routine finds the intesection of the line from 
// (px[0],py[0]) to (px[1],py[1]) to the line from (sx1,sy1) to (sx2, sy2).
//
//
static void getSegIntersection(double& xI, double& yI, double* px, double* py, 
double sx1, double sy1, double sx2, double sy2);

//
// This routine determines the intersection of the segment from
// (x1,y1) to (x2,y2) with the segments comprising the boundary of
// the rectangular domain [xMin,xMax] x [yMin, yMax].
//
//
static void getBoundaryIntersection(double& xI, double& yI, double x1, double y1,
double x2, double y2, double xMin, double xMax, double yMin,double yMax);

};
#endif 
