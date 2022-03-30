#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <moonbeam/dependencies.hpp>

namespace MoonBeam { namespace Graphics {
struct Vertex {  
  glm::vec4 point;
  glm::vec3 normal;
  glm::vec2 uv;

  static Vertex CreateVertex(glm::vec4 point, glm::vec2 uv, glm::vec3 normal);
  bool operator==(const Vertex& other) const;
  bool operator!=(const Vertex& other) const;
};

const glm::vec2 zero2(0);
const glm::vec3 zero3(0);
const glm::vec4 zero4(0);

}}

#endif