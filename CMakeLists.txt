project(Habari)

cmake_minimum_required(3.1)

option(HABARI_BUILD_EXAMPLE OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("${CMAKE_PROJECT_SOURCE_DIR}/include")

set(SOURCES
	source/Habari/Habari.cpp
)

add_library(Habari STATIC ${SOURCES})

if (HABARI_BUILD_EXAMPLE)
	set(EXAMPLE_SOURCES example/Example.cpp)

	add_executable(Habari-example ${EXAMPLE_SOURCES})
endif()