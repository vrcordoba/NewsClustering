 
cmake_minimum_required(VERSION 2.8.11)
project(NewsClustering)

set(HEADER_FILES
   News.h
   NewspaperNews.h
   Utf8Constants.h
   StringUtilities.h
   NewsCluster.h
   NewsReader.h
   NewsReaderFromPlainText.h
   InvalidLocationException.h
   ExclusionList.h
   ExclusionListFromFile.h
   ClusteringCriterion.h
   MostMentionedEntityClusteringCriterion.h
   ThematicSimilarityClusteringCriterion.h
   Clusterizer.h
   ClusterWriter.h
   PlainTextClusterWriter.h
   ClusterizerOptions.h
   ClusterizerOptionParser.h
   ClusterizerFactory.h
   TwitterNews.h
   NewsReaderFromTuit.h
   NewsDiscriminator.h
   NewsVisitor.h

   JsonCpp/json/json-forwards.h
   JsonCpp/json/json.h
)

set(SOURCE_FILES
   main.cpp

   News.cpp
   NewspaperNews.cpp
   StringUtilities.cpp
   NewsCluster.cpp
   NewsReaderFromPlainText.cpp
   InvalidLocationException.cpp
   ExclusionListFromFile.cpp
   MostMentionedEntityClusteringCriterion.cpp
   ThematicSimilarityClusteringCriterion.cpp
   Clusterizer.cpp
   PlainTextClusterWriter.cpp
   ClusterizerOptionParser.cpp
   ClusterizerFactory.cpp
   TwitterNews.cpp
   NewsReaderFromTuit.cpp
   NewsDiscriminator.cpp

   JsonCpp/jsoncpp.cpp
)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -g2")

include(cppcheck.cmake)

add_executable(newsClustering ${HEADER_FILES} ${SOURCE_FILES})
