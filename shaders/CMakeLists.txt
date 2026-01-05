add_executable(shaders
        ${COMMON_SOURCES}
        shaders.cpp
        ../shader.cpp
        ../shader.h)

target_include_directories(shaders PRIVATE ..)
target_link_libraries(shaders PRIVATE glfw)
configure_file(vertex.glsl ${CMAKE_CURRENT_BINARY_DIR}/vertex.glsl COPYONLY)
configure_file(fragment.glsl ${CMAKE_CURRENT_BINARY_DIR}/fragment.glsl COPYONLY)