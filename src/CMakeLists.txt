# CMakeLists.txt for creating a library

cmake_minimum_required(VERSION 3.10)
project(hls_parser)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(MY_SOURCES
	parse.cpp
	parse.cpp
	streaminfo.cpp
	tag.cpp 
	playlist.cpp
)

# Add the source files for the library${CMAKE_SOURCE_DIR}/src/
add_library(hls_parser ${MY_SOURCES})
message(CMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

# Specify include directories for the library (if needed)
target_include_directories(hls_parser PUBLIC ${CMAKE_SOURCE_DIR}/include/hls_parser)

# Specify installation location for the library
install(TARGETS hls_parser DESTINATION lib)
install(FILES hls_parser.h DESTINATION include/hls_parser) 