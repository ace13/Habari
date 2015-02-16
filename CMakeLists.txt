project(Habari)

cmake_minimum_required(VERSION 3.1)

option(HABARI_BUILD_EXAMPLE OFF)

if (NOT MSVC)
	set(CMAKE_CXX_STANDARD 11)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

set(SOURCES
	source/Habari/Habari.cpp
)

add_library(Habari STATIC ${SOURCES})

if (HABARI_BUILD_EXAMPLE)
	set(EXAMPLE_SOURCES example/Example.cpp)

	add_executable(Habari-example ${EXAMPLE_SOURCES})
	target_link_libraries(Habari-example Habari)
endif()