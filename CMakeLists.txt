project(LetterClustering)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
set (CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11")

set (EXECUTABLE_OUTPUT_PATH "${LetterClustering_BINARY_DIR}/bin")

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

install (DIRECTORY data DESTINATION "${LetterClustering_BINARY_DIR}")

add_subdirectory(src)
