cmake_minimum_required(VERSION 3.24)

project(
	numeric_exercises
	LANGUAGES CXX
)

list(
	APPEND CMAKE_MODULE_PATH
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/module"
)
include("get_cpm")
CPMUsePackageLock(package-lock.cmake)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory("src")
