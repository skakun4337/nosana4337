#include <moonbeam/graphics/texture2d.hpp>
#include <moonbeam/core/exception.hpp>
#include <stb_image.hpp>
#include <sstream>

using namespace MoonBeam;
using namespace Graphics;

Texture2D::Texture2D() {}

Texture2D::Texture2D(int width, int height) : Texture(width, height) {
  this->Bind();
  glActiveTexture(GL_TEXTURE0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
  glBindImageTexture(0, this->GetGLId(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}

Texture2D::Texture2D(std::string filepath) : Texture() {
  this->_filepath = filepath;
  this->Bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int nrChannels;
  unsigned char *data = stbi_load(filepath.c_str(), &this->_width, &this->_height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_width, this->_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
  } else {
    stbi_image_free(data);
    std::stringstream message;
    message << "Failed to load texture: " << filepath;
    throw Core::Exception(message.str());
  }
}

Texture2D::~Texture2D() {}

void Texture2D::Bind() {
  glBindTexture(GL_TEXTURE_2D, this->GetGLId());
}
