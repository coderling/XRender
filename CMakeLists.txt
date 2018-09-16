cmake_minimum_required(VERSION 2.6)
project(XRender)

# add FindSDL.camke path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${XRender_SOURCE_DIR}/cmake")

# set bin dir
set(BIN_DIR ${XRender_SOURCE_DIR}/bin)

set(SDL2_PATH /usr/local/Cellar/sdl2/2.0.7)
# set complier c++ flag for msvc or gnu&Clang
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -02")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    if (CMAKE_CXX_FLAGS MATCHES "/w[0-4]")
        string(REGEX REPLACE "/w[0-4]" "/w4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w4")
    endif()
endif()

# find the SDL2 package
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${XRender_SOURCE_DIR})
add_subdirectory(code)
