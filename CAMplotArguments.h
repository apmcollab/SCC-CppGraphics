#ifndef __CAMPLOTARGUMENTS__
#define __CAMPLOTARGUMENTS__
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
//  This class contains pointers to arguments to a graphics plot call
//
class CAMplotArguments
{

public :

    long callType;     // method type 1 : plot(y,n)
                       // method type 2 : plot(y,n,c)
                       // method type 3 : plot(y,n,c,s)

                       // method type 11 : plot(x,y,n,c)
                       // method type 12 : plot(x,y,n,c,s)
                       // method type 13 : plot(x,y,n,c)

    long      n;       // number of points
    long      s;       // style parameter
    char      c;       // point type

    double*   x;       // data
    double*   y;
    long x_Size;       // Size of data
    long y_Size;

    CAMplotArguments()
    {
    callType = 0;
    n = 0; s = 0; c = ' ';
    x = 0; x_Size = 0;
    y = 0; y_Size = 0;
    };

};

#endif
 
