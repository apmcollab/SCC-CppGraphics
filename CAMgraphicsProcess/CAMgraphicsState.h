/*
 * CAMgraphicsState.h
 *
 *  Created on: Nov 20, 2023
 *      Author: anderson
 */
#include "../UCdriver.h"
#include "../UCcontour.h"
#include "../UCplot.h"
#include "../UCsurface.h"

#ifndef CAM_GRAPHICS_STATE_
#define CAM_GRAPHICS_STATE_
//
//  Class to store CAMgraphics state
//
class   CAMgraphicsState
{

public :

    CAMgraphicsState();
    CAMgraphicsState(UCdriver* D);

    ~CAMgraphicsState();

    CAMgraphicsState(const CAMgraphicsState& S);
    void operator=(const   CAMgraphicsState& S);

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
#endif /* CAM_GRAPHICS_STATE_ */
