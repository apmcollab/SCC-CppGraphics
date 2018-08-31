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

#include <iostream>
#include <string>
using namespace std;

#ifndef __BCPLUSPLUS__
void CAMgraphicsExit()
{
	cerr << " Fatal Error : Program Stopped " << endl;
	exit(1);
};
void CAMgraphicsExit(char* ErrorMessage)
{
	cerr << ErrorMessage << endl << endl << endl;
	cerr << " Fatal Error " << endl;
	exit(1);
};
#else
void CAMgraphicsExit()
{
    cerr << endl << endl;
    cerr << "Hit return to Exit " << endl << endl;
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
CAMgraphicsException::CAMgraphicsException(char* Emessage)
{
    errorMessage = new char[strlen(Emessage) + 1];
    strcpy(errorMessage, Emessage);
}
CAMgraphicsException::CAMgraphicsException(const CAMgraphicsException& C)
{
    errorMessage = new char[strlen(C.errorMessage) + 1];
    strcpy(errorMessage, C.errorMessage);
}
CAMgraphicsException::~CAMgraphicsException()
{
    delete [] errorMessage;
}
#endif 
