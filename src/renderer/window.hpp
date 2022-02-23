#ifndef SRC_RENDERER_WINDOW_HPP
#define SRC_RENDERER_WINDOW_HPP

namespace renderer {
class Window {
 public:
  Window();
  ~Window();
  void createWindow(int width, int height, const char* name) const;
};
}  // namespace renderer

#endif
