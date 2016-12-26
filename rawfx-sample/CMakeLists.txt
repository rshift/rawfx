cmake_minimum_required(VERSION 3.6)
project(rawfx-sample)

set(SOURCE_FILES
    src/main.cpp
    )
add_executable(rawfx-sample ${SOURCE_FILES}
    )

target_link_libraries(rawfx-sample glfw rawfx-core)
