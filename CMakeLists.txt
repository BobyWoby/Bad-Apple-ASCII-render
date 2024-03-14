cmake_minimum_required(VERSION 3.22)
project(BadAppleASCII)

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

#find_package(SDL2_ttf REQUIRED)
#include_directories(${SDL2_TTF_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 17)
add_executable(BadAppleASCII WIN32 main.cpp)

target_link_libraries( BadAppleASCII ${OpenCV_LIBS})
target_link_libraries( BadAppleASCII ${SDL2_LIBRARIES})
#target_link_libraries( BadAppleASCII ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
