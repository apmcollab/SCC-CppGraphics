#ifndef __CAMTEXTARGUMENTS__
#define __CAMTEXTARGUMENTS__
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
class  CAMtextArguments
{
public :

    long callType;

    double     x;
    double     y;
    double  size;        // size of characters (-1 => use default size)

    char* s;
    long s_Size;

    CAMtextArguments()
    {
    callType = 0;
    x = 0.0;    y = 0.0; size = 0.0;
    s = 0; s_Size = 0;
    };
};
#endif
 
