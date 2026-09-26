cmake_minimum_required(VERSION 3.16)

project(ToolCL VERSION 0.4.5 LANGUAGES C)

message(STATUS "Configuring ToolCL ${PROJECT_VERSION}")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(TOOLCL_BUILD_EXAMPLES "Build ToolCL examples" ON)
option(TOOLCL_BUILD_3D "Build ToolCL 3D examples" ON)
option(TOOLCL_BUILD_TESTS "Build ToolCL tests" ON)
option(TOOLCL_FETCH_3D_DEPS "Fetch GLFW and GLEW when unavailable" ON)

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
    add_executable(hello_world examples/experimental/hello_world.c)
    target_link_libraries(hello_world PRIVATE toolcl)

    add_executable(hello_random examples/experimental/hello_random.c)
    target_link_libraries(hello_random PRIVATE toolcl)

    if(TOOLCL_BUILD_3D)
        find_package(OpenGL REQUIRED)
        find_package(PkgConfig QUIET)

        if(PkgConfig_FOUND)
            pkg_check_modules(GLFW3 QUIET IMPORTED_TARGET glfw3)
            pkg_check_modules(GLEW QUIET IMPORTED_TARGET glew)
        endif()

        if(TARGET PkgConfig::GLFW3)
            set(TOOLCL_GLFW_TARGET PkgConfig::GLFW3)
        elseif(TOOLCL_FETCH_3D_DEPS)
            include(FetchContent)

            FetchContent_Declare(
                glfw
                GIT_REPOSITORY https://github.com/glfw/glfw.git
                GIT_TAG 3.4
            )

            set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
            set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
            set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

            FetchContent_MakeAvailable(glfw)

            set(TOOLCL_GLFW_TARGET glfw)
        else()
            message(FATAL_ERROR "GLFW3 not found")
        endif()

        if(TARGET PkgConfig::GLEW)
            set(TOOLCL_GLEW_TARGET PkgConfig::GLEW)
        elseif(TOOLCL_FETCH_3D_DEPS)
            include(FetchContent)

            FetchContent_Declare(
                glew
                GIT_REPOSITORY https://github.com/nigels-com/glew.git
                GIT_TAG glew-2.2.0
                SOURCE_SUBDIR build/cmake
            )

            set(BUILD_UTILS OFF CACHE BOOL "" FORCE)
            set(BUILD_FRAMEWORK OFF CACHE BOOL "" FORCE)

            FetchContent_MakeAvailable(glew)

            if(TARGET glew_s)
                set(TOOLCL_GLEW_TARGET glew_s)
            elseif(TARGET glew)
                set(TOOLCL_GLEW_TARGET glew)
            else()
                message(FATAL_ERROR "GLEW target was not created")
            endif()
        else()
            message(FATAL_ERROR "GLEW not found")
        endif()

        foreach(example
            hello_3d
            hello_3d_vsync
            hello_3d_lighting
            hello_3d_lighting_vsync
        )
            add_executable(
                ${example}
                examples/3d/${example}.c
                examples/3d/hello_3d_common.c
            )

            target_include_directories(
                ${example}
                PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/examples/3d
            )

            target_link_libraries(
                ${example}
                PRIVATE
                toolcl
                ${TOOLCL_GLFW_TARGET}
                ${TOOLCL_GLEW_TARGET}
                OpenGL::GL
            )
        endforeach()
    endif()
endif()

if(TOOLCL_BUILD_TESTS)
    enable_testing()

    foreach(test
        test_logger
        test_math
        test_string
        test_vec
        test_mat4
    )
        add_executable(${test} tests/${test}.c)
        target_link_libraries(${test} PRIVATE toolcl)
        add_test(NAME ${test} COMMAND ${test})
    endforeach()
endif()
