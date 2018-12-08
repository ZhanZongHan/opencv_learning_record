cmake_minimum_required(VERSION 3.12)
project(test3)

set(CMAKE_CXX_STANDARD 14)

add_executable(test3 main.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(test3 ${OpenCV_LIBS})