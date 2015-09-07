cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

SET(CMAKE_FIND_ROOT_PATH $ENV{HOME}/arjan/rpi/rootfs)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

project( iCaldo )

file(GLOB_RECURSE iCaldo_SOURCES "*.cpp")
file(GLOB_RECURSE iCaldo_HEADERS "*.h")

#set (iCaldo_INCLUDE_DIRS "")
#foreach (_headerFile ${iCaldo_HEADERS})
#    get_filename_component(_dir ${_headerFile} PATH)
#    list (APPEND iCaldo_INCLUDE_DIRS ${_dir})
#endforeach()
#list(REMOVE_DUPLICATES iCaldo_INCLUDE_DIRS)

#include_directories(${iCaldo_INCLUDE_DIRS})

add_executable( iCaldo ${iCaldo_SOURCES} )