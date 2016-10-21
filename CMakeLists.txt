cmake_minimum_required(VERSION 3.0)
project(pgm2png)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

find_package(OpenCV REQUIRED)

set(SOURCE_FILES src/main.cpp)

add_executable(pgm2png ${SOURCE_FILES})

target_link_libraries(pgm2png ${OpenCV_LIBS})

