#include <moonbeam/graphics/texture.hpp>

using namespace MoonBeam;
using namespace Graphics;

Texture::Texture() {
  glGenTextures(1, RefGLId());
}

Texture::Texture(int width, int height) : Texture() {
  this->_width = width;
  this->_height = height;
}

Texture::~Texture() {
  // glDeleteTextures(1, &this->_id);
}

int Texture::GetHeight() const {
  return this->_height;
}

int Texture::GetWidth() const {
  return this->_width;
}
