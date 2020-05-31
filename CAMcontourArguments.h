#ifndef CAMCONTOURARGUMENTS__
#define CAMCONTOURARGUMENTS__

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
class  CAMcontourArguments
{
public :

    int callType;    // method type 0 : contour()
                     // method type 1 : contour(z,n,m)
                     // method type 2 : contour(z,n,m,n_c)
                     // method type 3 : contour(z,n,m,c_inc)
                     // method type 4 : contour(z,n,m,c_min, c_max)
                     // method type 5 : contour(z,n,m,n_c,c_min, c_max)
                     // method type 6 : contour(z,n,m,c_inc,c_min, c_max)
                     // method type 7 : contour(z,n,m,c_values, n_c)
                     // method type 8 : set_default_color(defaultColor)

    long n;
    long m;

    double c_min;
    double c_max;
    double c_inc;
    long     n_c;

    double* c_values;
    double* z;   // data : store as one dimensional

    long c_values_Size;
    long z_Size;

    int defaultColor;

    CAMcontourArguments()
    {
     callType = 0;
     m     = 0;   n     = 0;   n_c   = 0;
     c_min = 0.0; c_max = 0.0; c_inc = 0.0;
     c_values = 0; c_values_Size = 0;
     z        = 0; z_Size        = 0;
     defaultColor  = 0;
    };


};
#endif
 
