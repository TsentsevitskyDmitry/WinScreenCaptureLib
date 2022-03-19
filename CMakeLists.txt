cmake_minimum_required(VERSION 3.5)
project (WSCL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
    WSCL/ScreenCapture.h
    WSCL/IScreenCapture.h
    WSCL/D3D9ScreenCapture.h)

set(SOURCES
    WSCL/IScreenCapture.cpp
    WSCL/D3D9ScreenCapture.cpp)

source_group("Source Files" FILES ${SOURCES})
source_group("Header Files" FILES ${HEADERS})

set(PROJECT_CONTENT ${SOURCES} ${HEADERS})

add_library(${PROJECT_NAME} ${PROJECT_CONTENT})
add_library(WSCL::WSCL ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR})

find_package(OpenCV REQUIRED)
include_directories(${PROJECT_NAME} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${OpenCV_LIBS})
