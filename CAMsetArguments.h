#include <vector>
#include <string>

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

    std::vector<long>   i;    // for int arguments
    std::vector<double> d;    // for double arguments
    std::string         b;    // for string arguments

    CAMsetArguments()
    {
     callType = 0;
    };

};
#endif
 
