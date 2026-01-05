add_executable(textures
        ${COMMON_SOURCES}
        textures.cpp
        ../shader.cpp
        ../shader.h)

target_include_directories(textures PRIVATE ..)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../texturefiles"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/..")

target_link_libraries(textures PRIVATE glfw)
configure_file(vertex.glsl   ${CMAKE_CURRENT_BINARY_DIR}/vertex.glsl COPYONLY)
configure_file(fragment.glsl ${CMAKE_CURRENT_BINARY_DIR}/fragment.glsl COPYONLY)