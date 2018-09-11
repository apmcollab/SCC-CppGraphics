#
# This makefile builds the camgraphics support library. 
#
#

SHELL=/bin/sh
  

# Location of source and target binary files

SRC_DIR        =    ./test
LOCAL_INCLUDES = -I ../src -I .

LIB_LOC   = -L ../lib

ifeq ($(MAKECMDGOALS),release)
LIBS       = -lcamgraph
else
LIBS       = -lcamgraph_debug
endif


# Dependencies include all .h .cpp source files 

CPPfiles     = $(wildcard *.cpp)
CPPexecs     = $(patsubst %.cpp,%,$(wildcard *.cpp))

release:  $(CPPexecs) $(CPPfiles)

debug:    $(CPPexecs) $(CPPfiles)
	
% : %.cpp
	$(CXX) $(LOCAL_INCLUDES) $(LIB_LOC) $(CXXFLAGS) $(CXXDEFINES) $< $(LIBS) -o $@.exe
             
.PHONY : clean
clean  :
	-rm *.exe