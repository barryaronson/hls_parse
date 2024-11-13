cmake_minimum_required(VERSION 3.10)
project(hls_parser_example)

# Add your source files
add_executable(hls_parser_example hls_parser_example.cpp)

target_include_directories(hls_parser_example PRIVATE ${CMAKE_SOURCE_DIR}/include/hls_parser)

# Link the GoogleTest library to your test executable
target_link_libraries(hls_parser_example ${CMAKE_SOURCE_DIR}/build/src/libhls_parser.a)