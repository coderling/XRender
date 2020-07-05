cmake_minimum_required(VERSION 3.5)
project(XRenderTest VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(XRenderTest 
test_xrender_loop.cpp
test_color_shader.h
test_random_color_shader.h
test_create_scene.h
test_pipeline.h
)

target_include_directories(XRenderTest PRIVATE ../include)

target_link_libraries(XRenderTest XRenderLib)

install(TARGETS XRenderTest DESTINATION ${CMAKE_SOURCE_DIR}/bin)