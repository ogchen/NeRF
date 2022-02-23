#ifndef SRC_RENDERER_CONFIG_HPP
#define SRC_RENDERER_CONFIG_HPP

#include <glm/glm.hpp>

namespace renderer {
struct Config {
  using Colour = glm::vec4;

  int width;
  int height;
  const char *name;
  Colour colour;
};
}  // namespace renderer

#endif
