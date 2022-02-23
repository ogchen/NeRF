add_executable(NeRF "main.cpp" "renderer/window.hpp" "renderer/window.cpp" "renderer/renderer.hpp"  "renderer/renderer.cpp")
target_include_directories(NeRF PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(NeRF PRIVATE glfw)
target_link_libraries(NeRF PRIVATE glad::glad)