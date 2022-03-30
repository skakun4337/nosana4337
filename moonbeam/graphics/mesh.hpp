#ifndef MESH_HPP
#define MESH_HPP

#include <moonbeam/dependencies.hpp>
#include <vector>

namespace MoonBeam { namespace Graphics {
class Mesh {
public:
  Mesh();
  virtual ~Mesh();

  void Draw();
  static void UnloadMemory();

  int AddVertex(const Vertex& vertex);
  void AddTri(const Vertex& v1, const Vertex& v2, const Vertex& v3);
private:
  unsigned int VAO, VBO, EBO;

  std::vector<Vertex> _vertices;
  std::vector<int> _indices;

  bool TestBuffers();
  void GenerateBuffers();
  void RemoveBuffers();
};
}}

#endif