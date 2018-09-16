

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
set(O_DIR core/Object)
add_library(GraphicsLib
            ${G_DIR}/DrawLine.cpp
            ${G_DIR}/DrawPoint.cpp
            ${O_DIR}/Cube.cpp
            ${O_DIR}/Object.cpp)
target_link_libraries(GraphicsLib BasicLib)
# end GraphicsLib

# begin BasicLib
set(BASIC_DIR core/basic)
add_library(BasicLib
    ${BASIC_DIR}/Util.cpp
    ${BASIC_DIR}/Camera.cpp)
# end BasicLib



add_subdirectory(app)
add_subdirectory(TestCpp)
