//******************************************************************************
//                    CAMGRAPHEXIT.CPP
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1997
//            7/16/97
//
//
//********************************************************************************
//
#include "camgraphexit.h"

//
// strcpy_s is not implemented as part of C++11 (arrgh) so this macro
// inserts strcpy calls.
//

#ifdef _MSC_VER
#define COPYSTR(dst,count,src) strcpy_s(dst,count,src)
#else
#define COPYSTR(dst,count,src) strcpy(dst,src)
#endif

#include <iostream>
#include <string>

#ifndef __BCPLUSPLUS__
void CAMgraphicsExit()
{
	std::cerr << " Fatal Error : Program Stopped " << std::endl;
	exit(1);
};
void CAMgraphicsExit(char* ErrorMessage)
{
	std::cerr << ErrorMessage << std::endl << std::endl << std::endl;
	std::cerr << " Fatal Error " << std::endl;
	exit(1);
};
#else
void CAMgraphicsExit()
{
    std::cerr << std::endl << std::endl;
    std::cerr << "Hit return to Exit " << std::endl << std::endl;
    getchar();
	throw CAMgraphicsException("Error In CAM geometric entity Classes");
};
void CAMgraphicsExit(char* ErrorMessage)
{
	 throw CAMgraphicsException(ErrorMessage);
};
CAMgraphicsException::CAMgraphicsException()
{
	errorMessage = new char[1];
	errorMessage[0] = '\0';
}
CAMgraphicsException::CAMgraphicsException(const char* Emessage)
{
    errorMessage = new char[strlen(Emessage) + 1];
    //strcpy(errorMessage, Emessage);
    COPYSTR(errorMessage,strlen(Emessage) + 1, Emessage);
}
CAMgraphicsException::CAMgraphicsException(const CAMgraphicsException& C)
{
    errorMessage = new char[strlen(C.errorMessage) + 1];
    //strcpy(errorMessage, C.errorMessage);
    COPYSTR(errorMessage, strlen(C.errorMessage) + 1, C.errorMessage)
}
CAMgraphicsException::~CAMgraphicsException()
{
    delete [] errorMessage;
}
#endif 
