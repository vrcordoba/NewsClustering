
cmake_minimum_required(VERSION 2.8.11)
project(NewsClusteringTests)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(/usr/include/gmock)

add_executable(ExclusionListTestSuite
   ExclusionListTestSuite.cpp
   ../src/ExclusionListFromFile.cpp
   ../src/StringUtilities.cpp)
target_link_libraries(ExclusionListTestSuite ${GTEST_LIBRARIES} pthread gmock_main gmock)

add_executable(NewspaperNewsTestSuite
   NewspaperNewsTestSuite.cpp
   ../src/NewspaperNews.cpp
   ../src/StringUtilities.cpp
   ../src/News.cpp)
target_link_libraries(NewspaperNewsTestSuite ${GTEST_LIBRARIES} pthread gmock_main gmock)

add_executable(NewsReaderTestSuite
   NewsReaderTestSuite.cpp
   ../src/NewsReaderFromPlainText.cpp
   ../src/ExclusionListFromFile.cpp
   ../src/InvalidDirectoryException.cpp
   ../src/NewspaperNews.cpp
   ../src/StringUtilities.cpp
   ../src/NewsCluster.cpp
   ../src/News.cpp)
target_link_libraries(NewsReaderTestSuite ${GTEST_LIBRARIES} pthread gmock_main gmock)

add_executable(NewsClusterTestSuite
   NewsClusterTestSuite.cpp
   ../src/NewsCluster.cpp
   ../src/News.cpp)
target_link_libraries(NewsClusterTestSuite ${GTEST_LIBRARIES} pthread gmock_main gmock)

add_executable(MostMentionedEntityClusteringCriterionTestSuite
   MostMentionedEntityClusteringCriterionTestSuite.cpp
   ../src/MostMentionedEntityClusteringCriterion.cpp
   ../src/NewsCluster.cpp
   ../src/News.cpp)
target_link_libraries(MostMentionedEntityClusteringCriterionTestSuite ${GTEST_LIBRARIES} pthread gmock_main gmock)

add_executable(ClusterizerTestSuite
   ClusterizerTestSuite.cpp
   ../src/Clusterizer.cpp
   ../src/NewsCluster.cpp
   ../src/News.cpp)
target_link_libraries(ClusterizerTestSuite ${GTEST_LIBRARIES} pthread gmock_main gmock)

add_executable(RealClusterizerTestSuite
   RealClusterizerTestSuite.cpp
   ../src/Clusterizer.cpp
   ../src/MostMentionedEntityClusteringCriterion.cpp
   ../src/ThematicSimilarityClusteringCriterion.cpp
   ../src/NewsReaderFromPlainText.cpp
   ../src/ExclusionListFromFile.cpp
   ../src/InvalidDirectoryException.cpp
   ../src/NewspaperNews.cpp
   ../src/StringUtilities.cpp
   ../src/NewsCluster.cpp
   ../src/News.cpp)
target_link_libraries(RealClusterizerTestSuite ${GTEST_LIBRARIES} pthread gmock_main gmock)

add_executable(PlainTextClusterWriterTestSuite
   PlainTextClusterWriterTestSuite.cpp
   ../src/PlainTextClusterWriter.cpp
   ../src/NewsCluster.cpp
   ../src/InvalidDirectoryException.cpp
   ../src/News.cpp)
target_link_libraries(PlainTextClusterWriterTestSuite ${GTEST_LIBRARIES} pthread gmock_main gmock)

add_executable(ThematicSimilarityClusteringCriterionTestSuite
   ThematicSimilarityClusteringCriterionTestSuite.cpp
   ../src/ThematicSimilarityClusteringCriterion.cpp
   ../src/MostMentionedEntityClusteringCriterion.cpp
   ../src/NewsCluster.cpp
   ../src/News.cpp)
target_link_libraries(ThematicSimilarityClusteringCriterionTestSuite ${GTEST_LIBRARIES} pthread gmock_main gmock)

add_executable(ClusterizerOptionParserTestSuite
   ClusterizerOptionParserTestSuite.cpp
   ../src/ClusterizerOptionParser.cpp)
target_link_libraries(ClusterizerOptionParserTestSuite ${GTEST_LIBRARIES} pthread gmock_main gmock)

add_executable(TwitterNewsTestSuite
   TwitterNewsTestSuite.cpp
   ../src/TwitterNews.cpp
   ../src/StringUtilities.cpp
   ../src/News.cpp)
target_link_libraries(TwitterNewsTestSuite ${GTEST_LIBRARIES} pthread gmock_main gmock)
