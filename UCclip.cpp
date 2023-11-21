//
//******************************************************************************
//                              UCCLIP.CPP
//******************************************************************************
//
//            SOURCE FILE FOR CLASS UCclip 
//
//********************************************************************************
//            Chris Anderson                (C) UCLA 2003
//
//           
// Source Construction Date : 01/03/03 
//                           
//        
//********************************************************************************
//
#include <math.h>

#include "UCclip.h"

//
// This routine determines the number of points that need to
// be plotted when "smart" clipping is done. This routine is called before
// to determine the size of the xClip and yClip arrays used as arguments to the 
// getClippledPoints(...) member function.
//
long  UCclip::getClippedPlotPointCount(double* xP, double* yP, long n, double xMin,
double xMax, double yMin, double yMax)
{
    if(n == 1) return 1;

    long pCount = 0;

    long k;
//
//  First point
//
    k = 0;  

    pCount += 1; 
//
//  Intermediate points
//
    for(k = 1; k < n-1; k++)
    {

    if(inRegion(xP[k],yP[k],xMin,xMax,yMin,yMax))
    {pCount  += 1;} // pt inside
    else if(
    !(inRegion(xP[k-1],yP[k-1],xMin,xMax,yMin,yMax))&&
    !(inRegion(xP[k+1],yP[k+1],xMin,xMax,yMin,yMax)))
    {pCount  += 1;} // pt outside, prev outside, next outside 
    else if(!(inRegion(xP[k-1],yP[k-1],xMin,xMax,yMin,yMax)))
    {pCount  += 1;} // pt outside, prev outside, next inside
    else if(!(inRegion(xP[k+1],yP[k+1],xMin,xMax,yMin,yMax)))
    {pCount  += 1;} // pt outside, prev inside, next outside
    else // pt outside, prev inside, next inside
    {pCount  += 2;}

    }
//
//  Final point
//
    pCount += 1;

    return pCount;
}
//
// createClippedPoints(...) creates entries in the arrays xClip and yClip that are 
// the coordinates of the clipped polyline whose coordinates are specified in the
// arrays xP and yP. xClip and yClip must be allocated externally to this routine,
// and have a size that is greater than the value returned by the 
// getClippedPlotPointCount(...) member function. 
//
//
void UCclip::createClippedPoints(double* xClip,double* yClip, double* xP, double*yP, 
long n, double xMin, double xMax, double yMin, double yMax)
{
    if(n == 1) 
    {
    xClip[0] = xP[0];
    yClip[0] = yP[0];
    return;
    }

    long pCount = 0;

    long k;
//
//  First point
//
    k = 0;  
    if(inRegion(xP[k],yP[k],xMin,xMax,yMin,yMax))
    { // pt inside
     xClip[pCount] = xP[0];
     yClip[pCount] = yP[0];
     pCount  += 1;
    }
    else if(inRegion(xP[k+1],yP[k+1],xMin,xMax,yMin,yMax))
    { // pt outside, next inside
     getBoundaryIntersection(xClip[pCount],yClip[pCount],
     xP[k],yP[k],xP[k+1],yP[k+1],xMin,xMax,yMin,yMax);
     pCount  += 1;
    }
    else
    { // pt outside, next outside
     getBoundaryProjection(xClip[pCount],yClip[pCount],
     xP[k],yP[k],xMin,xMax,yMin,yMax);
     pCount  += 1;
    }
//
//  Intermediate points
//
    for(k = 1; k < n-1; k++)
    {

    if(inRegion(xP[k],yP[k],xMin,xMax,yMin,yMax))
    { // pt inside
     xClip[pCount] = xP[k];
     yClip[pCount] = yP[k];
     pCount  += 1;
    } 
    else if(
    !(inRegion(xP[k-1],yP[k-1],xMin,xMax,yMin,yMax))&&
    !(inRegion(xP[k+1],yP[k+1],xMin,xMax,yMin,yMax)))
    { // pt outside, prev outside, next outside 
     getBoundaryProjection(xClip[pCount],yClip[pCount],
     xP[k],yP[k],xMin,xMax,yMin,yMax);
     pCount  += 1;
    } 
    else if(!(inRegion(xP[k-1],yP[k-1],xMin,xMax,yMin,yMax)))
    {// pt outside, prev outside, next inside
     getBoundaryIntersection(xClip[pCount],yClip[pCount],
     xP[k],yP[k],xP[k+1],yP[k+1],xMin,xMax,yMin,yMax);
     pCount  += 1;
    } 
    else if(!(inRegion(xP[k+1],yP[k+1],xMin,xMax,yMin,yMax)))
    { // pt outside, prev inside, next outside
     getBoundaryIntersection(xClip[pCount],yClip[pCount],
     xP[k-1],yP[k-1],xP[k],yP[k],xMin,xMax,yMin,yMax);
     pCount  += 1;
    } 
    else // pt outside, prev inside, next inside
    {
     getBoundaryIntersection(xClip[pCount],yClip[pCount],
     xP[k-1],yP[k-1],xP[k],yP[k],xMin,xMax,yMin,yMax);
     pCount  += 1;

     getBoundaryIntersection(xClip[pCount],yClip[pCount],
     xP[k],yP[k],xP[k+1],yP[k+1],xMin,xMax,yMin,yMax);
     pCount  += 1;
    }

    }
//
//  Final point
//
    k = n-1;  
    if(inRegion(xP[k],yP[k],xMin,xMax,yMin,yMax))
    { // pt inside
     xClip[pCount] = xP[k];
     yClip[pCount] = yP[k];
     pCount  += 1;
    }
    else if(inRegion(xP[k-1],yP[k-1],xMin,xMax,yMin,yMax))
    { // pt outside, previous inside
     getBoundaryIntersection(xClip[pCount],yClip[pCount],
     xP[k-1],yP[k-1],xP[k],yP[k],xMin,xMax,yMin,yMax);
     pCount  += 1;
    }
    else
    { // pt outside, prev outside
     getBoundaryProjection(xClip[pCount],yClip[pCount],
     xP[k],yP[k],xMin,xMax,yMin,yMax);
     pCount  += 1;
    }

}
//
// This routine determines the horizontal and vertical projection 
// of the point (x,y) onto the boundary of the region [xMin,xMax]x[yMin,yMax]
//
void UCclip::getBoundaryProjection(double& xProj, double& yProj, double x, double y,
double xMin, double xMax, double yMin, double yMax)
{
    xProj = x;
    yProj = y;
    if(x > xMax) xProj = xMax;
    if(x < xMin) xProj = xMin;
    if(y > yMax) yProj = yMax;
    if(y < yMin) yProj = yMin;
}
//
// This routine determines if the point (x,y) is in the region
// [xMin,xMax] x [yMin,yMax]
//
int UCclip::inRegion(double x, double y, double xMin, double xMax, 
double yMin, double yMax)
{
    return ((x >= xMin)&&(x <= xMax)&&(y >= yMin)&&(y <= yMax));
}
//
// This routine finds the intesection of the line from 
// (px[0],py[0]) to (px[1],py[1]) to the line from (sx1,sy1) to (sx2, sy2).
//
//
void UCclip::getSegIntersection(double& xI, double& yI, double* px, double* py, 
double sx1, double sy1, double sx2, double sy2)
{
    double v1 = px[1] - px[0];
    double v2 = py[1] - py[0];

    double w1 = -(sx2 - sx1);
    double w2 = -(sy2 - sy1);

    double b1 = sx1 - px[0];
    double b2 = sy1 - py[0];

    double s; // double t;
    double det = w2*v1 - w1*v2;

    s = (1.0/det)*(w2*b1  - w1*b2);
    //t = (1.0/det)*(-v2*b1 + v1*b2);

    xI = (1.0 - s)*px[0] + s*px[1];
    yI = (1.0 - s)*py[0] + s*py[1];

    return;
}
//
// This routine determines the intersection of the segment from
// (x1,y1) to (x2,y2) with the segments comprising the boundary of
// the rectangular domain [xMin,xMax] x [yMin, yMax].
//
//
void UCclip::getBoundaryIntersection(double& xI, double& yI, double x1, double y1,
double x2, double y2, double xMin, double xMax, double yMin,double yMax)
{
    double px[2];
    double py[2];
    double slopeA;
    double slopeB;

    if(inRegion(x1,y1,xMin,xMax,yMin,yMax))
    {px[0] = x1; px[1] = x2; py[0] = y1; py[1] = y2;}
    else 
    {px[0] = x2; px[1] = x1; py[0] = y2; py[1] = y1;}

    if((yMin <= py[1])&&(py[1] <= yMax))
    {
    if(px[1] <= xMin) getSegIntersection(xI,yI,px,py,xMin,yMin,xMin,yMax);
    else              getSegIntersection(xI,yI,px,py,xMax,yMin,xMax,yMax);
    return;
    }

    if((xMin <= px[1])&&(px[1] <= xMax))
    {
    if(py[1] <= yMin) getSegIntersection(xI,yI,px,py,xMin,yMin,xMax,yMin);
    else              getSegIntersection(xI,yI,px,py,xMin,yMax,xMax,yMax);
    return;
    }

    if((xMax <= px[1])&&(yMax <= py[1]))
    {
    slopeA = (py[1] - py[0])/(px[1] - px[0]);
    slopeB = (yMax  - py[0])/(xMax  - px[0]);
    if(slopeA > slopeB) getSegIntersection(xI,yI,px,py,xMin,yMax,xMax,yMax);
    else                getSegIntersection(xI,yI,px,py,xMax,yMin,xMax,yMax);
    return;
    }

    
    if((xMin >= px[1])&&(yMax <= py[1]))
    {
    slopeA = (py[1] - py[0])/(px[1] - px[0]);
    slopeB = (yMax  - py[0])/(xMin  - px[0]);
    if(slopeA < slopeB) getSegIntersection(xI,yI,px,py,xMin,yMax,xMax,yMax);
    else                getSegIntersection(xI,yI,px,py,xMin,yMin,xMin,yMax);
    return;
    }

    if((xMin >= px[1])&&(yMin >=  py[1]))
    {
    slopeA = (py[1] - py[0])/(px[1] - px[0]);
    slopeB = (yMin - py[0])/(xMin  - px[0]);
    if(slopeA < slopeB) getSegIntersection(xI,yI,px,py,xMin,yMin,xMin,yMax);
    else                getSegIntersection(xI,yI,px,py,xMin,yMin,xMax,yMin);
    return;
    }

    if((xMax <= px[1])&&(yMin >=  py[1]))
    {
    slopeA = (py[1] - py[0])/(px[1] - px[0]);
    slopeB = (yMin - py[0])/(xMax  - px[0]);
    if(slopeA < slopeB) getSegIntersection(xI,yI,px,py,xMin,yMin,xMax,yMin);
    else                getSegIntersection(xI,yI,px,py,xMax,yMin,xMax,yMax);
    return;
    }

} 
