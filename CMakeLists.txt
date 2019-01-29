project(NAT_Penetrate)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
#set( CMAKE_C_COMPILER         /czx/application/gcc-linaro-arm-linux-gnueabihf-4.9_0614/bin/arm-linux-gnueabihf-gcc )
#set( CMAKE_CXX_COMPILER       /czx/application/gcc-linaro-arm-linux-gnueabihf-4.9_0614/bin/arm-linux-gnueabihf-g++ )

#SET( CMAKE_CXX_FLAGS           "${ARM_C_CXX_FLAGS} "   CACHE STRING "c++ flags" )
#SET( CMAKE_C_FLAGS             "${ARM_C_CXX_FLAGS} "   CACHE STRING "c flags" )
#set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  ")

set(CMAKE_CXX_FLAGS_DEBUG   "$ENV{CXXFLAGS} -O0 -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -fpermissive -fno-strict-aliasing -fopenmp")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall  -fopenmp")


add_subdirectory(Server)
add_subdirectory(NAT_A)
add_subdirectory(NAT_B)
