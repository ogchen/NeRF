cmake_minimum_required(VERSION 3.13)

project(NeRF)

if (NOT MSVC)
	message(FATAL_ERROR "MSVC not found")
endif ()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Torch CONFIG REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_subdirectory("src")
