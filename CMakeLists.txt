cmake_minimum_required(VERSION 3.5)
project(XTiny VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(XTiny App.cpp)

target_include_directories(XTiny PRIVATE ${PROJECT_SOURCE_DIR}/include)

install(TARGETS XTiny DESTINATION ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(thirdParty)