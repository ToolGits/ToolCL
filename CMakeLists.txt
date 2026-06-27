cmake_minimum_required(VERSION 3.10)

project(ToolCL VERSION 0.2.0 LANGUAGES C)

message(STATUS "Configuring ToolCL ${PROJECT_VERSION}")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# =========================
# OPTIONS
# =========================

option(TOOLCL_BUILD_EXAMPLES "Build ToolCL examples" ON)

# =========================
# OUTPUT DIRECTORIES
# =========================

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# =========================
# LIBRARY
# =========================

set(TOOLCL_SOURCES
    src/logger.c
    src/math.c
    src/vec2.c
    src/string.c
    src/hello_world.c
)

add_library(toolcl STATIC
    ${TOOLCL_SOURCES}
)

target_include_directories(toolcl PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# =========================
# EXAMPLES
# =========================

if(TOOLCL_BUILD_EXAMPLES)

add_executable(hello_logger
    examples/hello_logger.c
)

add_executable(hello_math
    examples/hello_math.c
)

add_executable(hello_vec2
    examples/hello_vec2.c
)

add_executable(hello_string
    examples/hello_string.c
)

add_executable(hello_world
    examples/hello_world.c
)

# =========================
# LINK EXAMPLES
# =========================

foreach(example
    hello_logger
    hello_math
    hello_vec2
    hello_string
    hello_world
)
    target_link_libraries(${example} PRIVATE toolcl)
endforeach()

# =========================
# EXAMPLES TARGET
# =========================

add_custom_target(examples
    DEPENDS
        hello_logger
        hello_math
        hello_vec2
        hello_string
        hello_world
)

endif()