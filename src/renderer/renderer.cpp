#include <renderer/renderer.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace renderer {

void initializeGLAD() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw RendererError("Failed to initialize GLAD");
  }
}

}  // namespace renderer
