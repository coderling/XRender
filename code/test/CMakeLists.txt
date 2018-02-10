project(helloSDL)
add_executable(helloSDL helloSDL.cpp)
target_link_libraries(helloSDL ${SDL2_LIBRARY})
install(TARGETS helloSDL RUNTIME DESTINATION ${BIN_DIR})
