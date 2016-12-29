cmake_minimum_required(VERSION 3.6)
project(rawfx)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories("${GLEW_INCLUDE_DIRS}" "${OPENGL_INCLUDE_DIR}" "rawfx-core/inc")

SET(BUILD_SHARED_LIBS ON)

add_subdirectory(thirdparty/glfw)

add_subdirectory(rawfx-core)
add_subdirectory(rawfx-sample)

