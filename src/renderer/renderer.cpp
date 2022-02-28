#include <renderer/renderer.hpp>
#include <renderer/error.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace renderer {

Renderer::Renderer(const Window::Factory &windowFactory,
                   const Window::Config &windowConfig,
                   std::span<ShaderInfo> shaders, const glm::vec4 &clearColor)
    : window_(windowFactory.createWindow(windowConfig)),
      shaderProgram_(compileShaders(shaders)) {
  glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

  GLuint buffer;
  glGenBuffers(1, &buffer);
  glGenVertexArrays(1, &arrayObject_);

  glBindVertexArray(arrayObject_);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

bool Renderer::shouldContinue() {
  return not glfwWindowShouldClose(window_.getWindow());
}

void Renderer::cycle() {
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shaderProgram_);
  glBindVertexArray(arrayObject_);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glfwSwapBuffers(window_.getWindow());
  glfwPollEvents();
}
}  // namespace renderer
