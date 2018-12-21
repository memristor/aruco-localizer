cmake_minimum_required(VERSION 3.12)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(
    ArUcoLocalizer
)

add_executable( 
    ArUcoLocalizer
    localizer.cpp
)

find_package( OpenCV REQUIRED )

target_link_libraries( ArUcoLocalizer ${OpenCV_LIBS} )