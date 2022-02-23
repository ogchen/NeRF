#include <renderer/window.hpp>
#include <renderer/renderer.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstddef>
#include <string>

namespace renderer {

Window::Window(Config config) : config_(config) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  createWindow(config_.width, config_.height, config_.name);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw RendererError("Failed to initialize GLAD");
  }

  glfwSetFramebufferSizeCallback(window_, Window::resizeViewport);

  auto colour = config_.colour;
  glClearColor(colour.r, colour.g, colour.b, colour.a);
}

Window::~Window() { glfwTerminate(); }

void Window::createWindow(int width, int height, const char* name) {
  window_ = glfwCreateWindow(width, height, name, nullptr, nullptr);
  if (window_ == nullptr) {
    throw RendererError("Failed to create GLFW window");
  }
  glfwMakeContextCurrent(window_);
}

void Window::resizeViewport(GLFWwindow*, int width, int height) {
  glViewport(0, 0, width, height);
}

bool Window::shouldClose() { return glfwWindowShouldClose(window_); }

void Window::cycle() {
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window_);
  glfwPollEvents();
}
}  // namespace renderer
