#include <vector>

#ifndef CAM_REGION_ARGUMENTS__
#define CAM_REGION_ARGUMENTS__
//
//######################################################################
//
//            Chris Anderson (C) UCLA
//
//                 Sept. 17, 1996
//
//######################################################################
//
//
//  This class contains pointers to arguments to a graphics region call
//
class CAMregionArguments
{

public :

    long callType;     // method type 1 : region(x, y, n, color, rgb)


    long      n;       // number of points

    double*   x;       // data
    double*   y;
    std::vector<double>  rgb;
    int     col;

    long x_Size;       // Size of data
    long y_Size;

    CAMregionArguments()
    {
    callType = 0;
    n = 0;
    col = 0;
    rgb.resize(3,0.0);
    x = 0; x_Size = 0;
    y = 0; y_Size = 0;
    };

};

#endif
 
