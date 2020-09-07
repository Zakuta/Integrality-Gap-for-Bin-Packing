cmake_minimum_required(VERSION 3.17)
project(BinPackingSolver)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64 -g -Wall -Wextra -pedantic")

set(GUROBI_INCLUDE_DIRECTORY "/home/pately/Desktop/EA-course/PA/bp-instance-generator-solver/Gurobi/gurobi903/linux64/include")

include_directories(${GUROBI_INCLUDE_DIRECTORY})

set(GUROBI_LIB_DIRECTORY "/home/pately/Desktop/EA-course/PA/bp-instance-generator-solver/Gurobi/gurobi903/linux64/lib")

link_directories(${GUROBI_LIB_DIRECTORY})

set(SOURCE_FILES arguments.cpp helper.cpp colgensolver.cpp bpinstance.cpp simplelpsolver.cpp main.cpp simpleipsolver.cpp solution.cpp datahandler.cpp modifiedkantorovichipsolver.cpp ${GUROBI_INCLUDE_DIRECTORY}/gurobi_c++.h ${GUROBI_LIB_DIRECTORY})
add_executable(BinPackingSolver ${SOURCE_FILES})

target_link_libraries (BinPackingSolver gurobi_c++)
target_link_libraries (BinPackingSolver gurobi90)