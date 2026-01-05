add_executable(hellotriangle
        hellotriangles.cpp ${COMMON_SOURCES}
        ../shader.cpp
        ../shader.h
)

target_include_directories(hellotriangle PRIVATE ..)
target_link_libraries(hellotriangle PRIVATE glfw)