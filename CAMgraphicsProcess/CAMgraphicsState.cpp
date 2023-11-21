/*
 * CAMgraphicsState.cpp
 *
 *  Created on: Nov 20, 2023
 *      Author: anderson
 */
//
//******************************************************************************
//                          CAMGRAPHICSSTATE.CPP
//******************************************************************************
//
#include "CAMgraphicsState.h"

CAMgraphicsState::CAMgraphicsState()
{
    frameLeft             = 0.14;
    frameRight            = 0.94;
    frameBottom           = 0.1;
    frameTop              = 0.9;
    plotRegionIndex       = 1;
    plotRegionRows        = 1;
    plotRegionIndexBound  = 1;
    defaultDriverFlag     = 0;
    OutputDeviceDriver    = 0;
    UCplotPointerArray    = new UCplot*[1];
    UCcontourPointerArray = new UCcontour*[1];
    UCsurfacePointerArray = new UCsurface*[1];
};

CAMgraphicsState::~CAMgraphicsState()
{
    if(plotRegionIndexBound > 0)
    {
      delete [] UCplotPointerArray;
      delete [] UCcontourPointerArray;
      delete [] UCsurfacePointerArray;
    }
};

CAMgraphicsState::CAMgraphicsState(const CAMgraphicsState& S)
{
    int i;
//
//  delete *this entries
//
    if(plotRegionIndexBound > 0)
    {
      delete [] UCplotPointerArray;
      delete [] UCcontourPointerArray;
      delete [] UCsurfacePointerArray;

      frameLeft             = 0.0;
      frameRight            = 0.0;
      frameBottom           = 0.0;
      frameTop              = 0.0;
      plotRegionIndex       = 0;
      plotRegionRows        = 0;
      defaultDriverFlag     = 0;
      OutputDeviceDriver    = 0;
    }
    plotRegionIndexBound  = 0;
//
//  Allocate and Copy
//
    if(S.plotRegionIndexBound > 0)
    {
    UCplotPointerArray    = new UCplot*[S.plotRegionIndexBound];
    UCcontourPointerArray = new UCcontour*[S.plotRegionIndexBound];
    UCsurfacePointerArray = new UCsurface*[S.plotRegionIndexBound];
    for(i = 0; i < S.plotRegionIndexBound; i++)
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
    plotRegionIndex       = S.plotRegionIndex ;
    plotRegionRows        = S.plotRegionRows;
    defaultDriverFlag     = S.defaultDriverFlag;
    OutputDeviceDriver    = S.OutputDeviceDriver;
    }

};

void CAMgraphicsState::operator=(const CAMgraphicsState& S)
{
    int i;
//
//  delete *this entries
//
    if(plotRegionIndexBound > 0)
    {
      delete [] UCplotPointerArray;
      delete [] UCcontourPointerArray;
      delete [] UCsurfacePointerArray;

      frameLeft             = 0.0;
      frameRight            = 0.0;
      frameBottom           = 0.0;
      frameTop              = 0.0;
      plotRegionIndex       = 0;
      plotRegionRows        = 0;
      defaultDriverFlag     = 0;
      OutputDeviceDriver    = 0;
    }
    plotRegionIndexBound  = 0;
//
//  Allocate and Copy
//
    if(S.plotRegionIndexBound > 0)
    {
    UCplotPointerArray    = new UCplot*[S.plotRegionIndexBound];
    UCcontourPointerArray = new UCcontour*[S.plotRegionIndexBound];
    UCsurfacePointerArray = new UCsurface*[S.plotRegionIndexBound];
    for(i = 0; i < S.plotRegionIndexBound; i++)
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
    plotRegionIndex       = S.plotRegionIndex ;
    plotRegionRows        = S.plotRegionRows;
    defaultDriverFlag     = S.defaultDriverFlag;
    OutputDeviceDriver    = S.OutputDeviceDriver;
    }

};


void CAMgraphicsState::setDriver(UCdriver* D)
{
    OutputDeviceDriver = D;
    defaultDriverFlag  = 0;
}



