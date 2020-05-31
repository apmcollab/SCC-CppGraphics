#ifndef CAMSETARGUMENTS__
#define CAMSETARGUMENTS__
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
//
class  CAMsetArguments
{

public :

    long callType;

    long*          i;    // for int arguments
    double*        d;    // for double arguments
    const char*    b;    // for string arguments

    long i_Size; long d_Size; long b_Size;

    CAMsetArguments()
    {
     callType = 0;
     i = 0;  i_Size = 0;
     d = 0;  d_Size = 0;
     b = 0;  b_Size = 0;
    };

};
#endif
 
