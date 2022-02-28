#include <renderer/renderer.hpp>
#include <renderer/window.hpp>
#include <renderer/shader.hpp>

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

void configureLogging() {
#ifdef NDEBUG
  spdlog::set_level(spdlog::level::info);
#else
  spdlog::set_level(spdlog::level::debug);
#endif
}

std::string readFile(const std::string& filePath) {
  std::ifstream fileStream(filePath);
  std::stringstream buffer;
  buffer << fileStream.rdbuf();
  return buffer.str();
}

renderer::Renderer createRenderer() {
  const renderer::Window::Factory& windowFactory =
      renderer::Window::Factory::getInstance();
  renderer::Window::Config windowConfig{
      .width = 800, .height = 600, .name = "NeRF"};
  std::vector<renderer::ShaderInfo> shaders{
      renderer::ShaderInfo{GL_VERTEX_SHADER, readFile("shaders/triangle.vert")},
      renderer::ShaderInfo{GL_FRAGMENT_SHADER,
                           readFile("shaders/triangle.frag")}};
  glm::vec4 clearColor{0.5f, 0.3f, 0.4f, 1.0f};
  return renderer::Renderer(windowFactory, windowConfig, shaders, clearColor);
}

int main() {
  configureLogging();
  renderer::Renderer renderer(createRenderer());
  while (renderer.shouldContinue()) {
    renderer.cycle();
  }
}
