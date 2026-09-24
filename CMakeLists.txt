cmake_minimum_required(VERSION 3.10)

project(ToolCL VERSION 0.3.0 LANGUAGES C)

message(STATUS "Configuring ToolCL ${PROJECT_VERSION}")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(TOOLCL_BUILD_EXAMPLES "Build ToolCL examples" ON)
option(TOOLCL_BUILD_3D_EXAMPLE "Build ToolCL OpenGL 3D example" OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

set(TOOLCL_SOURCES
    src/logger.c
    src/math.c
    src/vec2.c
    src/vec3.c
    src/mat4.c
    src/string.c
)

add_library(toolcl STATIC ${TOOLCL_SOURCES})

target_include_directories(toolcl PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# vec2 uses sqrtf(), which requires libm on typical Unix toolchains.
if(UNIX)
    target_link_libraries(toolcl PUBLIC m)
endif()

if(TOOLCL_BUILD_EXAMPLES)

    set(TOOLCL_EXAMPLES
        hello_logger
        hello_math
        hello_vec2
        hello_string
        hello_world
        hello_random
    )

    add_executable(hello_logger examples/hello_logger.c)
    add_executable(hello_math examples/hello_math.c)
    add_executable(hello_vec2 examples/hello_vec2.c)
    add_executable(hello_string examples/hello_string.c)
    add_executable(hello_world examples/hello_world.c)
    add_executable(hello_random examples/hello_random.c)

    foreach(example IN LISTS TOOLCL_EXAMPLES)
        target_link_libraries(${example} PRIVATE toolcl)
    endforeach()

    add_custom_target(examples
        DEPENDS ${TOOLCL_EXAMPLES}
    )

endif()

if(TOOLCL_BUILD_3D_EXAMPLE)

    find_package(OpenGL REQUIRED)
    find_package(glfw3 CONFIG REQUIRED)
    find_package(GLEW REQUIRED)

    add_executable(hello_3d_lighting_vsync examples/hello_3d_lighting_vsync.c)

    target_link_libraries(hello_3d_lighting_vsync
        PRIVATE
        toolcl
        OpenGL::GL
        glfw
    )

    add_executable(hello_3d_lighting examples/hello_3d_lighting.c)

    target_link_libraries(hello_3d_lighting
        PRIVATE
        toolcl
        OpenGL::GL
        glfw
    )

    add_executable(hello_3d examples/hello_3d.c)
    add_executable(hello_3d_vsync examples/hello_3d_vsync.c)

    target_link_libraries(hello_3d
        PRIVATE
        toolcl
        OpenGL::GL
        glfw
    )

    target_link_libraries(hello_3d_vsync
        PRIVATE
        toolcl
        OpenGL::GL
        glfw
        GLEW::GLEW
    )

endif()
