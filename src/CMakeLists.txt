add_executable(NeRF "main.cpp")
target_link_libraries(NeRF PRIVATE glfw)
target_link_libraries(NeRF PRIVATE glad::glad)