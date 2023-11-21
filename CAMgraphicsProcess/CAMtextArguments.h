#include <string>

#ifndef CAMTEXTARGUMENTS__
#define CAMTEXTARGUMENTS__
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

    std::string s;

    CAMtextArguments()
    {
    callType = 0;
    x    = 0.0;
    y    = 0.0;
    size = 0.0;
    };
};
#endif
 
