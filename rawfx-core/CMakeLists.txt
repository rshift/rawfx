cmake_minimum_required(VERSION 3.6)
project(rawfx-core)

set(SOURCE_FILES

    inc/rawfx/dev/assert.h

    inc/rawfx/core/event.h
    src/rawfx/core/event.cpp

    inc/rawfx/core/handler.h

    inc/rawfx/core/engine.h
    src/rawfx/core/engine.cpp

    inc/rawfx/graphics/color.h

    inc/rawfx/comp/composite.h
    src/rawfx/comp/composite.cpp

    inc/rawfx/comp/background.h
    src/rawfx/comp/background.cpp

    inc/rawfx/comp/fps_counter.h
    src/rawfx/comp/fps_counter.cpp

    inc/rawfx/defs/loader.h
    src/rawfx/defs/loader.cpp

    inc/rawfx/util/random_access_iterator.h
    inc/rawfx/util/range.h
    inc/rawfx/util/algorithm.h
    inc/rawfx/math/generic_vec.h
    inc/rawfx/math/vec.h

    )

add_library(rawfx-core ${SOURCE_FILES})
target_link_libraries(rawfx-core "${OPENGL_gl_LIBRARY}" "${GLEW_LIBRARY}")

add_executable(rawfx-core_test
    test/main.cpp
    test/rawfx/comp/composite.cpp
    test/rawfx/defs/loader.cpp
    test/rawfx/util/range.cpp
    test/rawfx/math/vec.cpp
    )
target_include_directories(rawfx-core_test PUBLIC test ../thirdparty/Catch/single_include)
target_link_libraries(rawfx-core_test rawfx-core)

enable_testing()
add_test(NAME rawfx-core_test COMMAND rawfx-core_test)
