cmake_minimum_required (VERSION 3.0)
project (LightPractice)

set (CMAKE_CXX_STANDARD 11)

#set output folder
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#assimp 
set(BUILD_ASSIMP_SAMPLES FALSE)
set(BUILD_TESTS FALSE)

add_subdirectory(libs/glfw-3.2.1)
add_subdirectory(libs/assimp-4.1.0)

#include header files
include_directories(
	include/
	libs/glfw-3.2.1/include/ 
	libs/assimp-4.1.0/include/
	build/libs/assimp-4.1.0/include/
	)
file(GLOB SOURCES "src/*.c*")

add_executable(LightPractice ${SOURCES})

#find_package(glfw3 REQUIRED)
target_link_libraries(LightPractice glfw assimp)




