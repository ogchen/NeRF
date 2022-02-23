#include <renderer/window.hpp>
#include <renderer/renderer.hpp>

#include <GLFW/glfw3.h>

#include <cstddef>
#include <string>

namespace renderer {

Window::Window() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::createWindow(int width, int height, const char* name) const {
  GLFWwindow* window = glfwCreateWindow(width, height, name, nullptr, nullptr);
  if (window == nullptr) {
    throw RendererError("Failed to create GLFW window");
  }
  glfwMakeContextCurrent(window);
}

Window::~Window() { glfwTerminate(); }
}  // namespace renderer
