#include <renderer/window.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace renderer {
namespace {
void errorHandler(int error, const char *description) {
  spdlog::error("GLFW error with code {} and description {}", error,
                description);
}
}  // namespace

Window::Factory::Factory() {
  glfwSetErrorCallback(errorHandler);
  if (not glfwInit()) {
    throw Error("Failed to initialize GLFW");
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Window::Factory::~Factory() { glfwTerminate(); }

Window::Window(const Config &config) {
  window_ = glfwCreateWindow(config.width, config.height, config.name.c_str(),
                             nullptr, nullptr);
  if (window_ == nullptr) {
    throw Error("Failed to create GLFW window");
  }
  glfwMakeContextCurrent(window_);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw Error("Failed to initialize GLAD");
  }

  auto resizeViewport = [](GLFWwindow *, int width, int height) {
    glViewport(0, 0, width, height);
  };
  glfwSetFramebufferSizeCallback(window_, resizeViewport);
}

Window::~Window() { glfwDestroyWindow(window_); }

}  // namespace renderer
