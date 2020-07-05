cmake_minimum_required(VERSION 3.5)
project(XRenderLib VERSION 0.0.1 LANGUAGES CXX)

add_library(XRenderLib STATIC)
target_sources(XRenderLib PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/math/Math.cpp
${CMAKE_CURRENT_SOURCE_DIR}/resources/IO.cpp
${CMAKE_CURRENT_SOURCE_DIR}/resources/MeshLoader.cpp
${CMAKE_CURRENT_SOURCE_DIR}/resources/Resources.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Cull.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Graphics.cpp
${CMAKE_CURRENT_SOURCE_DIR}/GraphicsGlobalData.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Matrial.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Mesh.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Object.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Pipeline.cpp
${CMAKE_CURRENT_SOURCE_DIR}/RenderContext.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/RenderTarget.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Scene.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Texture2D.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp
${CMAKE_CURRENT_SOURCE_DIR}/UniqueId.cpp
${CMAKE_CURRENT_SOURCE_DIR}/XRender.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Color.cpp
${CMAKE_CURRENT_SOURCE_DIR}/platform/image/ImageRenderTarget.cpp)

target_include_directories(XRenderLib PUBLIC ${CMAKE_SOURCE_DIR}/thirdParty/include)

target_link_libraries(XRenderLib ThirdPartyLib)
