#ifndef SRC_RENDERER_WINDOW_HPP
#define SRC_RENDERER_WINDOW_HPP

#include <renderer/config.hpp>

class GLFWwindow;

namespace renderer {

class Window {
 public:
  Window(Config config);
  ~Window();

  bool shouldClose();
  void cycle();

 private:
  static void resizeViewport(GLFWwindow* window, int width, int height);
  void createWindow(int width, int height, const char* name);

  Config config_;
  GLFWwindow* window_ = nullptr;
};
}  // namespace renderer

#endif
