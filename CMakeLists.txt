cmake_minimum_required(VERSION 3.31.6)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 20)

# Find GLFW once for the whole project
find_package(glfw3 REQUIRED)

# Common files used by all chapters
set(COMMON_SOURCES
        "${PROJECT_SOURCE_DIR}/glad.c"
        "${PROJECT_SOURCE_DIR}/utils.cpp"
        "${PROJECT_SOURCE_DIR}/stb_image.cpp"
        CACHE INTERNAL "Shared sources for all subprojects"
)

# Apple-specific include path
if(APPLE)
    include_directories(~/include)
endif()

# Add subdirectories for each app
add_subdirectory(hellotriangle)
add_subdirectory(shaders)
add_subdirectory(textures)

