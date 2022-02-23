#include <renderer/renderer.hpp>
#include <renderer/window.hpp>

int main() {
  renderer::Window window;
  window.createWindow(800, 600, "Hello World");
  renderer::initializeGLAD();
}
