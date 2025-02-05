cmake_minimum_required(VERSION 3.10)
project(hls_parse_test)

# Find the needed libraries
find_package(GTest REQUIRED)
find_package(CURL REQUIRED)

# Add source files
add_executable(hls_parse_test main.cpp playlist_test.cpp parse_test.cpp byterange_test.cpp)

target_include_directories(hls_parse_test PRIVATE ${CMAKE_SOURCE_DIR}/include/hls_parse)

# Link the GoogleTest library to test executable
target_link_libraries(hls_parse_test GTest::gtest_main ${CMAKE_SOURCE_DIR}/build/src/libhls_parse.a CURL::libcurl)

# Enable testing
enable_testing()

# Add a test target
add_test(NAME hls_parse_test COMMAND hls_parse_test)