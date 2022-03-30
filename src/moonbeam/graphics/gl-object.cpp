#include <moonbeam/graphics/gl-object.hpp>

using namespace MoonBeam;
using namespace Graphics;

GLObject::GLObject() {}

GLObject::~GLObject() {}

unsigned int GLObject::GetGLId() const {
  return this->_gl_id;
}

unsigned int GLObject::GetGLType() const {
  return this->_gl_type;
}

unsigned int* GLObject::RefGLId() {
  return &this->_gl_id;
}

void GLObject::SetGLType(unsigned int type) {
  this->_gl_type = type;
}