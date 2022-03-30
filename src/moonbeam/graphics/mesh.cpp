#include <moonbeam/graphics/mesh.hpp>
#include <moonbeam/graphics/vertex.hpp>
#include <algorithm>

#include <iostream>

using namespace MoonBeam;
using namespace Graphics;

Mesh::Mesh() {}

Mesh::~Mesh() {
  this->RemoveBuffers();
}

void Mesh::Draw() {
  //if (!this->TestBuffers())
  //  this->GenerateBuffers();
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::UnloadMemory() {
  glBindVertexArray(0);
}

void Mesh::AddTri(const Vertex& v1, const Vertex& v2, const Vertex& v3) {
  int id;
  id = this->AddVertex(v1);
  this->_indices.push_back(id);
  id = this->AddVertex(v2);
  this->_indices.push_back(id);
  id = this->AddVertex(v3);
  this->_indices.push_back(id);

  this->RemoveBuffers();
  this->GenerateBuffers();
}

int Mesh::AddVertex(const Vertex& vertex) {
  // auto index = std::find(this->_vertices.begin(), this->_vertices.end(), vertex);
  // if (index != this->_vertices.end())
  //   return index - this->_vertices.begin();
  
  this->_vertices.push_back(vertex);
  return this->_vertices.size() -1;
}

void Mesh::GenerateBuffers() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * _indices.size(), _indices.data(), GL_STATIC_DRAW);

  // Positions
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glEnableVertexAttribArray(0);

  // Normals
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));
  glEnableVertexAttribArray(1);

  // UV
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, uv)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

bool Mesh::TestBuffers() {
  return glIsVertexArray(VAO) && glIsBuffer(VBO) && glIsBuffer(EBO);
}

void Mesh::RemoveBuffers() {
  if (glIsVertexArray(VAO))
    glDeleteVertexArrays(1, &VAO);
  if (glIsBuffer(VBO))
    glDeleteBuffers(1, &VBO);
  if (glIsBuffer(EBO))
    glDeleteBuffers(1, &EBO);
}