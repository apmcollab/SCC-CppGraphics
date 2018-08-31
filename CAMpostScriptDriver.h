#ifndef __CAMPSDRIVER__
#define __CAMPSDRIVER__
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
#include "CAMgraphicsDriver.h"

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

#ifndef _CAMGRAPHICS_
class CAMgraphicsState;
class CAMgraphics;
#endif

#include "camgraphimpexp.h"

class __IMPEXP__ CAMpostScriptDriver : public CAMgraphicsDriver
{

public  :

	CAMpostScriptDriver();
    CAMpostScriptDriver(const char* F);
    ~CAMpostScriptDriver();
    
	void open();
	void close();
	void frame();
	void accept(const CAMplotArguments& A);
	void accept(const CAMcontourArguments& A);
	void accept(const CAMsurfaceArguments& A);
	void accept(const CAMtextArguments& A);
 	void accept(const CAMsetArguments& A);


    void AddBackSlash(const char* in, char* out);

private :

   CAMgraphics* G;
   CAMgraphicsState* S;
   char* outputFile;

};
#endif 
