#ifndef SRC_RENDERER_ERROR_HPP
#define SRC_RENDERER_ERROR_HPP

#include <stdexcept>

namespace renderer {
class RendererError : public std::runtime_error {
  using std::runtime_error::runtime_error;
};
}  // namespace renderer

#endif
