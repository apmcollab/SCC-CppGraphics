cmake_minimum_required (VERSION 3.15)
project (CppGraphics)

file(GLOB Library_Sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" ) 

add_library (CppGraphics STATIC ${Library_Sources})

target_compile_features    (CppGraphics PUBLIC cxx_std_11)
target_include_directories (CppGraphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


