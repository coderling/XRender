cmake_minimum_required(VERSION 3.5)
project(XRenderTest LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(common_source
test_color_shader.h
test_random_color_shader.h
test_create_scene.h
test_pipeline.h
test_util.h
)

add_executable(XRenderTest 
test_xrender_loop.cpp)
target_sources(XRenderTest PRIVATE ${ommon_source})
target_include_directories(XRenderTest PRIVATE ../include PRIVATE ../Shaders PRIVATE ../PostProcessing)
target_link_libraries(XRenderTest XRenderLib)

add_executable(LambertLight 
test_lambert_lighting.cpp)
target_sources(LambertLight PRIVATE ${ommon_source})
target_include_directories(LambertLight PRIVATE ../include PRIVATE ../Shaders PRIVATE ../PostProcessing)
target_link_libraries(LambertLight XRenderLib)

add_executable(TestShadow
test_shadow.cpp)
target_sources(TestShadow PRIVATE ${ommon_source})
target_include_directories(TestShadow PRIVATE ../include PRIVATE ../Shaders PRIVATE ../PostProcessing)
target_link_libraries(TestShadow XRenderLib)

install(TARGETS XRenderTest LambertLight TestShadow DESTINATION ${CMAKE_SOURCE_DIR}/bin)