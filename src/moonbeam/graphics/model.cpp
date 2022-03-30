#include <moonbeam/graphics/model.hpp>
#include <moonbeam/graphics/mesh.hpp>
#include <moonbeam/graphics/shader.hpp>
#include <moonbeam/graphics/material.hpp>

using namespace MoonBeam;
using namespace Graphics;

Model::Model() {}

Model::~Model() {}

void Model::SetMaterial(const MaterialId& mat) {
  this->_material = mat;
}

void Model::SetMesh(Mesh* mesh) {
  this->_mesh = mesh;
}

MaterialId Model::GetMaterial() const {
  return this->_material;
}

Mesh* Model::GetMesh() const {
  return this->_mesh;
}
