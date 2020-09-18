cmake_minimum_required(VERSION 3.5)
project(XRenderLib VERSION 0.0.1 LANGUAGES CXX)

add_library(XRenderLib STATIC)
target_sources(XRenderLib PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/math/Math.cpp
${CMAKE_CURRENT_SOURCE_DIR}/resources/IO.cpp
${CMAKE_CURRENT_SOURCE_DIR}/resources/MeshLoader.cpp
${CMAKE_CURRENT_SOURCE_DIR}/resources/Texture2DLoader.cpp
${CMAKE_CURRENT_SOURCE_DIR}/resources/Resources.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Cull.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Graphics.cpp
${CMAKE_CURRENT_SOURCE_DIR}/GraphicsGlobalData.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Matrial.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Mesh.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Transform.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Object.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Pipeline.cpp
${CMAKE_CURRENT_SOURCE_DIR}/RenderContext.cpp
${CMAKE_CURRENT_SOURCE_DIR}/RenderTexture.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/RenderDevice.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Scene.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Texture2D.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Sampler2D.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp
${CMAKE_CURRENT_SOURCE_DIR}/UniqueId.cpp
${CMAKE_CURRENT_SOURCE_DIR}/XRender.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Color.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Lighting.cpp
${CMAKE_CURRENT_SOURCE_DIR}/XTime.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Bounds.cpp
${CMAKE_CURRENT_SOURCE_DIR}/ViewFrustum.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Shapes/Capsule.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Shapes/Cube.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Shapes/Panel.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Shapes/Sphere.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Shapes/ShapeData.cpp
${CMAKE_CURRENT_SOURCE_DIR}/ShadowMap.cpp
${CMAKE_CURRENT_SOURCE_DIR}/ShadowSetting.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Semantic.cpp
${CMAKE_CURRENT_SOURCE_DIR}/PostProcess/PostProcess.cpp
${CMAKE_CURRENT_SOURCE_DIR}/PostProcess/PostProcessContext.cpp
${CMAKE_CURRENT_SOURCE_DIR}/PostProcess/PostProcessEffect.cpp
${CMAKE_CURRENT_SOURCE_DIR}/platform/common/Platform.cpp)

if(USE_IMAGE_TARGET)
add_definitions(-DUSE_IMAGE_TARGET)
target_sources(XRenderLib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/image/ImageDevice.cpp)
elseif(WIN32)
target_sources(XRenderLib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/win/WindowsDevice.cpp)
else()
target_sources(XRenderLib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/image/ImageDevice.cpp)
endif()

target_include_directories(XRenderLib PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/include)

target_link_libraries(XRenderLib ThirdPartyLib)