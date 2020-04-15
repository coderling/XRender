cmake_minimum_required(VERSION 3.5)
project(XTiny)

add_executable(XTiny main.cpp tgaimage/tgaimage.cpp src/line.cpp)
target_include_directories(XTiny PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/tgaimage)

install(TARGETS XTiny DESTINATION ${PROJECT_SOURCE_DIR}/bin)