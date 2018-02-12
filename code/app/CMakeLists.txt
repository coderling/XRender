project(XApp)
add_executable(XApp XMain.cpp)
target_link_libraries(XApp ${SDL2_LIBRARY})
set(LIBRARY_OUTPUT_PATH ${BIN_DIR}/lib)
install(TARGETS XApp RUNTIME DESTINATION ${BIN_DIR})

# begin include 目录
# end include

# begin applib

add_library(XAppLib XApp.cpp)
target_link_libraries(XAppLib ${SDL2_LIBRARY})
target_link_libraries(XApp XAppLib)
# begin applib

# begin mathlib
set(MATH_DIR ../core/math)
add_library(XMathLib
            ${MATH_DIR}/EulerAngles.cpp
            ${MATH_DIR}/MathUtil.cpp
            ${MATH_DIR}/Matrix4x3.cpp
            ${MATH_DIR}/Quaternion.cpp
            ${MATH_DIR}/RotationMatrix.cpp)
target_link_libraries(XApp XMathLib)
# begin mathlib

# begin GraphicsLib
set(MATH_DIR ../core/primitive)
add_library(GraphicsLib
            ${MATH_DIR}/DrawLine.cpp
            ${MATH_DIR}/DrawPoint.cpp)
target_link_libraries(XApp GraphicsLib)
# end GraphicsLib