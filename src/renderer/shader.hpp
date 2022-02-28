#ifndef SRC_RENDERER_SHADER_HPP
#define SRC_RENDERER_SHADER_HPP

#include <glad/glad.h>

#include <string>
#include <span>

namespace renderer {
struct ShaderInfo {
  unsigned int type;
  std::string content;
};

GLuint compileShaders(std::span<ShaderInfo> shaders);
}  // namespace renderer

#endif
