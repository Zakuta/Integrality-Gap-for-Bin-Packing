cmake_minimum_required(VERSION 3.17)
project(bp-EA-course)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64 -g -Wall -Wextra -pedantic  -I/usr/local/include -L/usr/local/lib -lIOH")

set(GUROBI_INCLUDE_DIRECTORY "/Library/gurobi903/mac64/include/")

include_directories(${GUROBI_INCLUDE_DIRECTORY})

set(GUROBI_LIB_DIRECTORY "/Library/gurobi903/mac64/lib")
set(IOH_DIRECTORY "/usr/local/include")

link_directories(${GUROBI_LIB_DIRECTORY})

set(SOURCE_FILES src/simplelpsolver.cpp src/simpleipsolver.cpp src/solution.cpp ${GUROBI_INCLUDE_DIRECTORY}/gurobi_c++.h ${GUROBI_LIB_DIRECTORY} ${IOH_DIRECTORY} src/helper.cpp src/AIG_BP.hpp)

#add_executable(bpsolver ${SOURCE_FILES})
add_library(bpsolver ${SOURCE_FILES})
add_executable(main main.cpp)

#target_link_libraries (bpsolver gurobi_c++)
#target_link_libraries (bpsolver gurobi90)
target_link_libraries (main bpsolver)
target_link_libraries (main gurobi_c++)
target_link_libraries (main gurobi90)
