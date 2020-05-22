set(FileList test_xrender_loop.cpp
             ../src/Pipeline.cpp
             ../src/XRender.cpp)
add_executable(TestXRenderLoop ${FileList})
target_include_directories(TestXRenderLoop  PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/thirdParty)
install(TARGETS TestXRenderLoop DESTINATION ${PROJECT_SOURCE_DIR}/bin)