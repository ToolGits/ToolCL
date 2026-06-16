cmake_minimum_required(VERSION 3.10)

project(ToolCL C)

set(CMAKE_C_STANDARD 99)

add_library(toolcl
    src/logger.c
)

target_include_directories(toolcl PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(hello_logger
    examples/hello_logger.c
)

target_link_libraries(hello_logger
    toolcl
)