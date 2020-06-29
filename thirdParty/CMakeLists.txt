cmake_minimum_required(VERSION 3.5)

add_library(ThirdPartyLib
${CMAKE_CURRENT_SOURCE_DIR}/geometry.cpp
${CMAKE_CURRENT_SOURCE_DIR}/tgaimage.cpp
)

target_include_directories(ThirdPartyLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)