#
# This is the "meta" makefile that builds the sample executables
# by invoking their respective makescripts.
#
# Usage :
#
# make release                   === builds release versions of all executables
# make debug                     === builds debug versions of all executables
#
# make clean                     === removes object files and executables
# make cleanall                  === removes object files, executables and temporary directories
#
# 
# August 30, 2018
#
SHELL=/bin/sh

# Location of SCC source files and Makescripts files

SCC_Dir=../../SCC
MAKESCRIPTS_Dir=$(SCC_Dir)/MakeScripts

# Use BaseCommonConfig.mk if it exists, otherwise use BaseCommonConfig_Default.mk 

ifneq ("$(wildcard $(MAKESCRIPTS_Dir)/BaseCommonConfig.mk)","")
	include $(MAKESCRIPTS_Dir)/BaseCommonConfig.mk
else
	include $(MAKESCRIPTS_Dir)/BaseCommonConfig_Default.mk
endif


ifeq ($(MAKECMDGOALS),release)
BUILD_TYPE=release
endif
ifeq ($(MAKECMDGOALS),debug)
BUILD_TYPE=debug
endif


release : .Starting   .camgraphLib .camgraphTest    .Finished  

debug   : .Starting   .camgraphLib_debug .camgraphTest_debug    .Finished  

.Starting :
	###########################################################
	#            Build Started
	########################################################### 
	$(QUIET) echo "Compilation Date : " `date` 
ifeq ($(OpenMP),0)
	$(QUIET) echo "Executable Type  :  Single-threaded" 
else
	$(QUIET) echo "Executable Type  :  OpenMP based multi-threaded" 
endif


.camgraphLib  :
	###########################################################
	#               .camgraphLib 
	###########################################################
	$(QUIET)$(MAKE) -f  camgraphLib.mk    release 
.camgraphLib_debug :
	###########################################################
	#                .camgraphLib_debug
	########################################################### 
	$(QUIET)$(MAKE) -f   camgraphLib.mk   debug
	
 
.camgraphTest  :
	###########################################################
	#               .camgraphTest 
	###########################################################
	$(QUIET)$(MAKE) -f  Makefile  --directory=test/ release 
.camgraphTest_debug :
	###########################################################
	#                .camgraphTest_debug
	########################################################### 
	$(QUIET)$(MAKE) -f Makefile  --directory=test/ debug


.Finished :
	###########################################################
	#            Build Completed
	########################################################### 
.PHONY : cleanall clean
cleanall  : clean
	rm -rf ./_*
clean: 
	$(QUIET)$(MAKE) -f Makefile --directory=test/     clean 
	$(QUIET)$(MAKE) -f Makefile --directory=test/     clean
 



