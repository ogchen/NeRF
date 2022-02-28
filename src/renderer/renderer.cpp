#include <renderer/renderer.hpp>
#include <renderer/error.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <array>

namespace renderer {

Renderer::Renderer(Window::Factory &windowFactory,
                   const Window::Config &windowConfig,
                   std::span<ShaderInfo> shaders, const glm::vec4 &clearColor)
    : window_(windowFactory.createWindow(windowConfig)),
      clearColor_(clearColor) {
  glClearColor(clearColor_.r, clearColor_.g, clearColor_.b, clearColor_.a);
  compileShaders(shaders);
}

bool Renderer::shouldContinue() {
  return not glfwWindowShouldClose(window_.getWindow());
}

void Renderer::cycle() {
  glClear(GL_COLOR_BUFFER_BIT);

  std::array vertices{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f),
                      glm::vec3(-0.5f, 0.0f, 0.0f)};

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
               GL_STATIC_DRAW);

  glfwSwapBuffers(window_.getWindow());
  glfwPollEvents();
}
}  // namespace renderer
