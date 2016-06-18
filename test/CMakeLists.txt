
cmake_minimum_required(VERSION 2.8.11)
project(NewsClusteringTests)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(/usr/include/gmock)

add_executable(ExclusionListTestSuite
   ExclusionListTestSuite.cpp
   ../src/ExclusionListFromFile.cpp)
target_link_libraries(ExclusionListTestSuite ${GTEST_LIBRARIES} pthread gmock_main gmock)
