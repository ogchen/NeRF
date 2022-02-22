cmake_minimum_required(VERSION 3.13)

project("NeRF")

if (NOT MSVC)
	message(FATAL_ERROR "MSVC not found")
endif ()

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_subdirectory("src")
