#include <renderer/shader.hpp>
#include <renderer/error.hpp>

#include <GLFW/glfw3.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <utility>
#include <string>
#include <vector>

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

std::pair<bool, std::string> getCompileStatus(GLuint id) {
  GLint success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  GLint logLength;
  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);

  std::string infoLog(logLength, ' ');
  glGetShaderInfoLog(id, logLength, nullptr, infoLog.data());

  return std::make_pair(static_cast<bool>(success), infoLog);
}

std::pair<bool, std::string> getLinkStatus(GLuint id) {
  GLint success;
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  GLint logLength;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);

  std::string infoLog(logLength, ' ');
  glGetProgramInfoLog(id, logLength, nullptr, infoLog.data());

  return std::make_pair(static_cast<bool>(success), infoLog);
}

GLuint compileShader(const ShaderInfo& info) {
  GLuint shaderID;
  shaderID = glCreateShader(info.type);
  const char* content = info.content.c_str();
  glShaderSource(shaderID, 1, &content, nullptr);
  glCompileShader(shaderID);

  std::string shaderType = getShaderType(info.type);
  const auto [success, infoLog] = getCompileStatus(shaderID);
  if (not success) {
    throw RendererError(fmt::format("Failed to compile {} shader with error {}",
                                    shaderType, infoLog));
  } else if (not infoLog.empty()) {
    spdlog::info("Compiled {} shader with log: {}", shaderType, infoLog);
  }
  return shaderID;
}
}  // namespace

GLuint compileShaders(std::span<ShaderInfo> shaders) {
  GLuint shaderProgram = glCreateProgram();
  std::vector<GLuint> shaderIDs;

  for (const auto& shader : shaders) {
    GLuint id = compileShader(shader);
    shaderIDs.push_back(id);
    glAttachShader(shaderProgram, id);
  }
  glLinkProgram(shaderProgram);

  const auto [success, infoLog] = getLinkStatus(shaderProgram);
  if (not success) {
    throw RendererError(
        fmt::format("Failed to link shaders with error {}", infoLog));
  } else if (not infoLog.empty()) {
    spdlog::info("Linked shaders with log: {}", infoLog);
  }

  glUseProgram(shaderProgram);
  for (const auto& id : shaderIDs) {
    glDeleteShader(id);
  }

  return shaderProgram;
}
}  // namespace renderer
