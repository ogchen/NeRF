#include <renderer/renderer.hpp>
#include <renderer/window.hpp>
#include <renderer/config.hpp>

int main() {
  renderer::Config config{
      .width = 800,
      .height = 600,
      .name = "NeRF",
      .colour = renderer::Config::Colour(0.2f, 0.3f, 0.3f, 1.0f)};
  renderer::Window window(config);
  while (not window.shouldClose()) {
    window.cycle();
  }
}
