cmake_minimum_required(VERSION 3.5)
project(XTiny)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(XTiny main.cpp
                    thirdParty/tgaimage.cpp
                    thirdParty/model.cpp
                    src/line.cpp)

target_include_directories(XTiny PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/thirdParty)

install(TARGETS XTiny DESTINATION ${PROJECT_SOURCE_DIR}/bin)