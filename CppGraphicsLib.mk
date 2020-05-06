#
# This makefile builds the CppGraphics support library. 
#
# Aug. 30, 2018

SHELL=/bin/sh

# Location of SCC source files and Makescripts files

SCC_Dir=../
MAKESCRIPTS_Dir=$(SCC_Dir)/MakeScripts

# Parameters for library construction script 

CXX     := g++
LIB_DIR = ./lib
SRC_DIR = ./

# Create library directory if it doesn't exist 

create_lib_dir := \
$(shell if [ ! -e $(LIB_DIR) ]; then mkdir $(LIB_DIR); fi) 

# specify make parameters

ifndef VERBOSE
QUIET     :=@
MAKEFLAGS += --no-print-directory
MAKEFLAGS := $(sort $(MAKEFLAGS))
endif

ifeq ($(MAKECMDGOALS),release)

CFLAGS      :=-O2  -fno-gcse -fno-optimize-sibling-calls -Wno-write-strings
CXXFLAGS    :=-O2  -fno-gcse -fno-optimize-sibling-calls -Wno-write-strings --std=c++11
CDEFINES    += 
CXXDEFINES  += 
endif

ifeq ($(MAKECMDGOALS),debug)
CFLAGS      =-g -Wall -fno-inline
CDEFINES    =-D_DEBUG
CXXFLAGS    =-g -Wall -fno-inline
CXXDEFINES  +=-D_DEBUG 
endif

RELEASE_DIR  = ./_releaseCppGraphics
DEBUG_DIR    = ./_debugCppGraphics

DEBUG_LIBRARY    = $(LIB_DIR)/libCppGraphics_debug.a
RELEASE_LIBRARY  = $(LIB_DIR)/libCppGraphics.a 

include $(MAKESCRIPTS_Dir)/CommonLibMake.mk
