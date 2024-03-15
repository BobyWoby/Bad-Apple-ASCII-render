cmake_minimum_required(VERSION 3.22)
project(BadAppleASCII)

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SFML 2.5 COMPONENTS audio system REQUIRED)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
#    # SFML version >= 2.5
#    #In SFML Version 2.5 or later, ${SFML_LIBRARIES}, ${SFML_DEPENDENCIES}, ${SFML_INCLUDE_DIR} no longer exist. Specify libraries individually.
#    target_link_libraries(BadAppleASCII sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
endif()
set(CMAKE_CXX_STANDARD 17)
add_executable(BadAppleASCII WIN32 main.cpp)

target_link_libraries( BadAppleASCII ${OpenCV_LIBS} ${SDL2_LIBRARIES} sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
install(TARGETS BadAppleASCII DESTINATION bin)