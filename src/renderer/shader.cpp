#include <renderer/shader.hpp>
#include <renderer/error.hpp>

#include <GLFW/glfw3.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <utility>
#include <string>

namespace renderer {
namespace {
std::string getShaderType(GLint shaderType) {
  switch (shaderType) {
    case GL_VERTEX_SHADER:
      return "vertex";
    case GL_GEOMETRY_SHADER:
      return "geometry";
    case GL_FRAGMENT_SHADER:
      return "fragment";
    default:
      return "unknown";
  }
}
}  // namespace

ShaderProgram::ShaderProgram(const std::vector<ShaderInfo>& shaders)
    : shaderProgram_(glCreateProgram()) {
  std::vector<GLuint> shaderIDs;

  for (const auto& shader : shaders) {
    GLuint id = compileShader(shader);
    shaderIDs.push_back(id);
    glAttachShader(shaderProgram_, id);
  }
  glLinkProgram(shaderProgram_);

  const auto [success, infoLog] = getLinkStatus(shaderProgram_);
  if (!success) {
    throw RendererError(
        fmt::format("Failed to link shaders with error {}", infoLog));
  } else if (!infoLog.empty()) {
    spdlog::info("Linked shaders with log: {}", infoLog);
  }

  for (const auto& id : shaderIDs) {
    glDeleteShader(id);
  }
}

ShaderProgram::~ShaderProgram() { glDeleteProgram(shaderProgram_); }

void ShaderProgram::use() const { glUseProgram(shaderProgram_); }

GLuint ShaderProgram::compileShader(const ShaderInfo& info) const {
  GLuint shaderID;
  shaderID = glCreateShader(info.type);
  const char* content = info.content.c_str();
  glShaderSource(shaderID, 1, &content, nullptr);
  glCompileShader(shaderID);

  std::string shaderType = getShaderType(info.type);
  const auto [success, infoLog] = getCompileStatus(shaderID);
  if (!success) {
    throw RendererError(fmt::format("Failed to compile {} shader with error {}",
                                    shaderType, infoLog));
  } else if (!infoLog.empty()) {
    spdlog::info("Compiled {} shader with log: {}", shaderType, infoLog);
  }
  return shaderID;
}

ShaderProgram::Status ShaderProgram::getCompileStatus(GLuint id) const {
  GLint success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  GLint logLength;
  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);

  std::string infoLog(logLength, ' ');
  glGetShaderInfoLog(id, logLength, nullptr, infoLog.data());

  return Status(static_cast<bool>(success), infoLog);
}

ShaderProgram::Status ShaderProgram::getLinkStatus(GLuint id) const {
  GLint success;
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  GLint logLength;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);

  std::string infoLog(logLength, ' ');
  glGetProgramInfoLog(id, logLength, nullptr, infoLog.data());

  return Status(static_cast<bool>(success), infoLog);
}
}  // namespace renderer
