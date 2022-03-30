#include <moonbeam/graphics/material.hpp>
#include <moonbeam/graphics/shader.hpp>
#include <moonbeam/graphics/texture.hpp>

#include <algorithm>

using namespace MoonBeam;
using namespace Graphics;

Material::Material() {}

Material::~Material() {}

ShaderId Material::GetShader() const {
  return this->_shader;
}

void Material::SetShader(const ShaderId& shader) {
  this->_shader = shader;
}

void Material::SetTexture(unsigned int index, const TextureId& tex) {
  this->_textures[index] = tex;
}

const std::map<unsigned int, TextureId>& Material::GetTexutres() const {
  return this->_textures;
}