cmake_minimum_required(VERSION 3.10)
project(hls_parser_test)

# Find the GoogleTest library
find_package(GTest REQUIRED)

# Add your source files
add_executable(hls_parser_test main.cpp playlist_test.cpp parse_test.cpp)

target_include_directories(hls_parser_test PRIVATE ${CMAKE_SOURCE_DIR}/include/hls_parser)

# Link the GoogleTest library to your test executable
target_link_libraries(hls_parser_test GTest::gtest_main ${CMAKE_SOURCE_DIR}/build/src/libhls_parser.a)

# Enable testing
enable_testing()

# Add a test target
add_test(NAME hls_parser_test COMMAND hls_parser_test)