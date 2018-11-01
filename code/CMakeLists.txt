


set(LIBRARY_OUTPUT_PATH ${BIN_DIR}/lib)

# begin include 目录
# end include

# begin applib
set(APP_DIR app)
add_library(XAppLib ${APP_DIR}/XApp.cpp)
target_link_libraries(XAppLib ${SDL2_LIBRARY})
# begin applib

# begin mathlib
set(MATH_DIR core/math)
add_library(XMathLib
            ${MATH_DIR}/EulerAngles.cpp
            ${MATH_DIR}/MathUtil.cpp
            ${MATH_DIR}/Matrix4x3.cpp
            ${MATH_DIR}/Quaternion.cpp
            ${MATH_DIR}/RotationMatrix.cpp)
# end mathlib

# begin GraphicsLib
set(G_DIR core/primitive)
set(O_DIR core/Objects)
set(R_DIR core/Render)
add_library(GraphicsLib
            ${G_DIR}/DrawLine.cpp
            ${G_DIR}/DrawPoint.cpp
            ${O_DIR}/Cube.cpp
            ${O_DIR}/Triangle.cpp
            ${R_DIR}/Renderer.cpp
            ${R_DIR}/Shader.cpp)
target_link_libraries(GraphicsLib BasicLib)
target_link_libraries(GraphicsLib XMathLib)
# end GraphicsLib

# begin BasicLib
set(BASIC_DIR core/basic)
add_library(BasicLib
    ${BASIC_DIR}/Util.cpp
    ${BASIC_DIR}/Camera.cpp
    ${BASIC_DIR}/BaseObject.cpp
    ${BASIC_DIR}/Object.cpp
    ${BASIC_DIR}/Behavior.cpp)
# end BasicLib



add_subdirectory(DemoApp)
#add_subdirectory(TestCpp)
