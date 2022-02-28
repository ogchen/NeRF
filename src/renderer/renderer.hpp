#ifndef SRC_RENDERER_RENDERER_HPP
#define SRC_RENDERER_RENDERER_HPP

#include <renderer/window.hpp>
#include <renderer/shader.hpp>

#include <glm/glm.hpp>

#include <vector>

class GLFWwindow;

namespace renderer {
class Renderer {
 public:
  Renderer(const Window::Factory &windowFactory,
           const Window::Config &windowConfig,
           const std::vector<ShaderInfo> &shaders, const glm::vec4 &clearColor);

  bool shouldContinue();
  void cycle();

 private:
  Window window_;
  ShaderProgram shaderProgram_;
  GLuint arrayObject_;
};
}  // namespace renderer

#endif
