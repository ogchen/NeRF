#ifndef SRC_RENDERER_WINDOW_HPP
#define SRC_RENDERER_WINDOW_HPP

#include <renderer/error.hpp>

#include <string>

class GLFWwindow;

namespace renderer {
class Window {
 public:
  struct Error : public RendererError {
    using RendererError::RendererError;
  };

  struct Config {
    int width;
    int height;
    std::string name;
  };

  class Factory {
   public:
    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;
    Factory(Factory&&) = delete;
    Factory& operator=(Factory&&) = delete;
    ~Factory();

    static Factory& getInstance() {
      static Factory factory;
      return factory;
    }

    Window createWindow(const Config& config) const { return Window(config); }

   private:
    Factory();
  };

 public:
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;
  Window(Window&&) = delete;
  Window& operator=(Window&&) = delete;
  ~Window();
  GLFWwindow* getWindow() { return window_; }

 private:
  explicit Window(const Config& config);
  GLFWwindow* window_ = nullptr;
};

}  // namespace renderer

#endif
