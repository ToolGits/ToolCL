cmake_minimum_required(VERSION 3.10)

project(ToolCL VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# =========================
# LIBRARY
# =========================

set(TOOLCL_SOURCES
    src/logger.c
    src/math.c
    src/vec2.c
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

add_executable(hello_logger
    examples/hello_logger.c
)

add_executable(hello_math
    examples/hello_math.c
)

add_executable(hello_vec2
    examples/hello_vec2.c
)

target_link_libraries(hello_logger toolcl)
target_link_libraries(hello_math toolcl)
target_link_libraries(hello_vec2 toolcl)