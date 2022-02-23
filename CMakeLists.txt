cmake_minimum_required(VERSION 3.13)

project(NeRF)

if (NOT MSVC)
	message(FATAL_ERROR "MSVC not found")
endif ()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_subdirectory("src")
