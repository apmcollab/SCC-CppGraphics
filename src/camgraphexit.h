//******************************************************************************
//                    CAMGRAPHEXIT.H
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
#ifndef __CAMGRAPHICSEXIT__
#define __CAMGRAPHICSEXIT__
#include <cstdlib>

#include "camgraphimpexp.h"

void __IMPEXP__ CAMgraphicsExit();
void __IMPEXP__ CAMgraphicsExit(char* ErrorMessage);

#ifdef __BCPLUSPLUS__

class __IMPEXP__ CAMgraphicsException
{
	public :

	CAMgraphicsException();
	CAMgraphicsException(const CAMgraphicsException& C);
	CAMgraphicsException(char* msg);
   ~CAMgraphicsException();
    
	char* getMessage() const {return errorMessage;};

	private :

	char* errorMessage;
};
#endif
#endif 
