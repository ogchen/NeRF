cmake_minimum_required(VERSION 3.13)

project("NeRF")

add_subdirectory("src")

if (NOT MSVC)
	message(FATAL_ERROR "MSVC not found")
endif ()
