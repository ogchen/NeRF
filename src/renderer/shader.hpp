#ifndef SRC_RENDERER_SHADER_HPP
#define SRC_RENDERER_SHADER_HPP

#include <glad/glad.h>

#include <string>
#include <vector>
#include <utility>

namespace renderer {
struct ShaderInfo {
  GLuint type;
  std::string content;
};

class ShaderProgram {
 public:
  explicit ShaderProgram(const std::vector<ShaderInfo> &shaders);
  ~ShaderProgram();
  void use() const;

 private:
  using Status = std::pair<bool, std::string>;

  GLuint compileShader(const ShaderInfo &info) const;
  Status getCompileStatus(GLuint id) const;
  Status getLinkStatus(GLuint id) const;

  GLuint shaderProgram_;
};

}  // namespace renderer

#endif
