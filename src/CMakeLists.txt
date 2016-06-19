 
cmake_minimum_required(VERSION 2.8.11)
project(NewsClustering)

set(HEADER_FILES
   Analizador.h
   EntidadNombrada.h
   Noticia.h

   News.h
   Utf8Constants.h
   ExclusionList.h
   ExclusionListFromFile.h
)

set(SOURCE_FILES
   Main.cpp
   Analizador.cpp
   EntidadNombrada.cpp
   Noticia.cpp

   News.cpp
   ExclusionListFromFile.cpp
)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -g2")

include(cppcheck.cmake)

add_executable(newsClustering ${HEADER_FILES} ${SOURCE_FILES})
