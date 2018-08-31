#ifndef __CAMGRAPHICSDRIVER__
#define __CAMGRAPHICSDRIVER__
//
//######################################################################
//
//            Chris Anderson (C) UCLA
//
//                 Sept. 17, 1996
//
// Jan. 25, 1999 :  Removed argument name from calling parameters
//######################################################################
//
#ifndef __CAMPLOTARGUMENTS__
class CAMplotArguments;
#endif

#ifndef __CAMCONTOURARGUMENTS__
class CAMcontourArguments;
#endif

#ifndef __CAMSURFACEARGUMENTS__
class CAMsurfaceArguments;
#endif

#ifndef __CAMTEXTARGUMENTS__
class CAMtextArguments;
#endif

#ifndef __CAMSETARGUMENTS__
class CAMsetArguments;
#endif

#include "camgraphimpexp.h"

class __IMPEXP__ CAMgraphicsDriver
{
    public :
    virtual ~CAMgraphicsDriver(){delete [] dTypeName;};
    virtual void accept(const  CAMplotArguments& /* P */) {};
    virtual void accept(const  CAMcontourArguments& /* C */) {};
    virtual void accept(const  CAMsurfaceArguments& /* S */) {};
    virtual void accept(const  CAMtextArguments& /* T */){};
    virtual void accept(const  CAMsetArguments& /* S */){};
    virtual void open() {};
    virtual void close(){};
    virtual void frame(){};
    virtual void reset(){};

    virtual char* getDriverTypeName(){return dTypeName;}

    char* dTypeName;
};
#endif
 
