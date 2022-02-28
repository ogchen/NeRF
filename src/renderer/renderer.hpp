#ifndef SRC_RENDERER_RENDERER_HPP
#define SRC_RENDERER_RENDERER_HPP

#include <renderer/window.hpp>
#include <renderer/shader.hpp>

#include <glm/glm.hpp>

#include <span>

class GLFWwindow;

namespace renderer {
class Renderer {
 public:
  Renderer(Window::Factory &windowFactory, const Window::Config &windowConfig,
           std::span<ShaderInfo> shaders, const glm::vec4 &clearColor);

  bool shouldContinue();
  void cycle();

 private:
  Window window_;
  glm::vec4 clearColor_;
};
}  // namespace renderer

#endif
