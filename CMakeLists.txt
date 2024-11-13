# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and optionally the language(s) used
project(hls_parse)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories containing source code
add_subdirectory(src)

# Add subdirectories containing tests (optional)
add_subdirectory(test)
add_subdirectory(example)