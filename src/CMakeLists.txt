# CMakeLists.txt for creating a library

cmake_minimum_required(VERSION 3.10)
project(hls_parse)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(MY_SOURCES
	byterange.cpp
	parse.cpp
	playlist.cpp
	streaminf.cpp
	tag.cpp 
)

# Add the source files for the library
add_library(hls_parse ${MY_SOURCES})
message(CMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

# Specify include directories for the library (if needed)
target_include_directories(hls_parse PUBLIC ${CMAKE_SOURCE_DIR}/include/hls_parse)

# Specify installation location for the library
install(TARGETS hls_parse DESTINATION lib)
install(FILES hls_parse.h DESTINATION include/hls_parse) 