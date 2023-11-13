//******************************************************************************
//                    CAMGRAPHEXIT.H
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 2023
//
//
//********************************************************************************
//
#include <iostream>
#include <string>
#include <stdexcept>

#ifndef CAMGRAPHICSEXIT_
#define CAMGRAPHICSEXIT_

static void CAMgraphicsExit()
{
	throw std::runtime_error("\nCppGraphics Fatal Error : Program Stopped \n");
};

static void CAMgraphicsExit(const std::string ErrorMessage)
{
	std::string errMsg = "\n";
	errMsg            += ErrorMessage;
	throw std::runtime_error(errMsg);
};

#endif 
