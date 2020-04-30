cmake_minimum_required (VERSION 3.15)
project (CppGraphicsTest)

OPTION(USE_CLEANUP "Use CLEANUP" OFF)
 
message(STATUS "System Name ${CMAKE_SYSTEM_NAME}")

# Suppresses the creation of the install script 

set(CMAKE_SKIP_INSTALL_RULES True)

# Loads helper to print messages 
include(CMakePrintHelpers)

set(ExternalLibs  CppGraphics )
add_subdirectory(${CMAKE_SOURCE_DIR}/.. ${CMAKE_SOURCE_DIR}/../build)


ADD_CUSTOM_TARGET(debug
  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
  COMMENT "Creating the executable in the debug mode.")

ADD_CUSTOM_TARGET(release
  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
  COMMENT "Creating the executable in the release mode.")



# Creating separate executables for each *.cpp file in the source directory 

file(GLOB Test_Sources  RELATIVE ${CMAKE_SOURCE_DIR} "*.cpp"   ) 
 
enable_testing()

set(OUTPUT_EXEC_EXT "")
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
set(OUTPUT_EXEC_EXT ".exe")
endif()

foreach( testfile ${Test_Sources} )
    string( REPLACE ".cpp" "" testname ${testfile} )
    add_executable( ${testname} ${testfile} )
#
#   Add dependent includes
#

#   target_sources( ${testname} PRIVATE MathVector.h MathMatrix.h )

	target_compile_features(${testname} PUBLIC cxx_std_11)
	set_target_properties  (${testname} PROPERTIES CXX_EXTENSIONS OFF)

#
#   Specify location of supporting components 
#

	target_include_directories(${testname} PRIVATE ${CMAKE_SOURCE_DIR}/..)

#
#  Required libraries 
#
    target_link_libraries(${testname}  PUBLIC "${ExternalLibs}")
#
#   Executable output properties 
#
	set_target_properties(${testname}  PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}" 
	OUTPUT_NAME "${testname}${OUTPUT_EXEC_EXT}")


add_test(NAME    ${testname} WORKING_DIRECTORY "./Testing/Temporary"
        COMMAND "${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/${testname}${OUTPUT_EXEC_EXT}")
endforeach()


#
# Test cleanup code 
#

if(USE_CLEANUP)
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
add_test(NAME cleanup  
         WORKING_DIRECTORY "./Testing/Temporary"
         COMMAND "${CMAKE_SOURCE_DIR}/cleanup.sh")
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
add_test(NAME cleanup  
         WORKING_DIRECTORY "./Testing/Temporary"
         COMMAND "${CMAKE_SOURCE_DIR}/cleanup.sh")
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
add_test(NAME cleanup  
         WORKING_DIRECTORY "./Testing/Temporary"
         COMMAND "${CMAKE_SOURCE_DIR}/cleanup.bat")
endif()
endif()

