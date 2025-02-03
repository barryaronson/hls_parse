cmake_minimum_required(VERSION 3.10)
project(hls_parse_example)

find_package(CURL REQUIRED)

# Add your source files
add_executable(hls_parse_example hls_parse_example.cpp)

target_include_directories(hls_parse_example PRIVATE ${CMAKE_SOURCE_DIR}/include/hls_parse)

# Link the GoogleTest library to your test executable
target_link_libraries(hls_parse_example ${CMAKE_SOURCE_DIR}/build/src/libhls_parse.a CURL::libcurl)