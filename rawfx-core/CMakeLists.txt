cmake_minimum_required(VERSION 3.6)
project(rawfx-core)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(SOURCE_FILES

    include/rawfx/core/event.h
    include/rawfx/core/handler.h
    include/rawfx/core/composite.h
    include/rawfx/core/engine.h

    src/rawfx/core/event.cpp
    src/rawfx/core/composite.cpp
    src/rawfx/core/engine.cpp

    )
include_directories(include "${GLEW_INCLUDE_DIRS}" "${OPENGL_INCLUDE_DIR}")

add_library(rawfx-core ${SOURCE_FILES})
target_link_libraries(rawfx-core ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARY})

add_executable(rawfx-core_test ${SOURCE_FILES}
    test/main.cpp
    test/rawfx/core/composite.cpp
    )
target_include_directories(rawfx-core_test PUBLIC test ../thirdparty/Catch/single_include)

enable_testing()
add_test(NAME rawfx-core_test COMMAND rawfx-core_test)
