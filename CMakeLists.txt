project(Habari)

cmake_minimum_required(3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("${CMAKE_PROJECT_SOURCE_DIR}/include")

set(SOURCES
	source/Habari/Habari.cpp
)

add_library(Habari STATIC ${SOURCES})
