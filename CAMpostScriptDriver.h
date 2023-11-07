#ifndef CAMPSDRIVER__
#define CAMPSDRIVER__
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
#include <string>
#include "CAMgraphicsDriver.h"


#ifndef CAMPLOTARGUMENTS__
class CAMplotArguments;
#endif

#ifndef CAM_REGION_ARGUMENTS__
class CAMregionArguments;
#endif

#ifndef CAMCONTOURARGUMENTS__
class CAMcontourArguments;
#endif

#ifndef CAMSURFACEARGUMENTS__
class CAMsurfaceArguments;
#endif

#ifndef CAMTEXTARGUMENTS__
class CAMtextArguments;
#endif

#ifndef CAMSETARGUMENTS__
class CAMsetArguments;
#endif

#ifndef CAMGRAPHICS_
class CAMgraphicsState;
class CAMgraphics;
#endif

#include "camgraphimpexp.h"

class __IMPEXP__ CAMpostScriptDriver : public CAMgraphicsDriver
{

public  :

	CAMpostScriptDriver();
    CAMpostScriptDriver(const std::string& outputFileName);
    virtual ~CAMpostScriptDriver();
    
	void open();
	void close();
	void frame();
	void accept(const CAMplotArguments& A);
	void accept(const CAMregionArguments& A);
	void accept(const CAMcontourArguments& A);
	void accept(const CAMsurfaceArguments& A);
	void accept(const CAMtextArguments& A);
 	void accept(const CAMsetArguments& A);

    void initialize(const std::string& outputFileName);

    void AddBackSlash(const char* in, char* out);

private :

   CAMgraphics* G;
   CAMgraphicsState* S;
   std::string outputFile;

};
#endif 
