#ifndef CAMSURFACEARGUMENTS__
#define CAMSURFACEARGUMENTS__
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
class  CAMsurfaceArguments
{

public :

    long callType;    // method type 0 : surface()
                     // method type 1 : surface(z,n,m)
                     // method type 2 : surfacez,n,m,x,y)

    long n;
    long m;
    double* z;   // data : store as one dimensional
    double* x;
    double* y;
    long z_Size;
    long x_Size;
    long y_Size;
    
    CAMsurfaceArguments()
    {
    callType = 0;
    m = 0; n = 0; 
    z = 0; z_Size = 0;
    x = 0; x_Size = 0;
    y = 0; y_Size = 0;
    };

};
#endif
 
