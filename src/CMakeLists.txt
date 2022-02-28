add_executable(
    NeRF
    "main.cpp"
    "renderer/window.hpp"
    "renderer/window.cpp"
    "renderer/error.hpp"
    "renderer/shader.cpp"
    "renderer/shader.hpp"
    "renderer/renderer.cpp"
    "renderer/renderer.hpp"
)

configure_file("renderer/shaders/triangle.vert" "shaders/triangle.vert" COPYONLY)
configure_file("renderer/shaders/triangle.frag" "shaders/triangle.frag" COPYONLY)

target_include_directories(NeRF PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(NeRF PRIVATE glfw)
target_link_libraries(NeRF PRIVATE glad::glad)
target_link_libraries(NeRF PRIVATE glm::glm)
target_link_libraries(NeRF PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
target_link_libraries(NeRF PRIVATE fmt::fmt-header-only)
