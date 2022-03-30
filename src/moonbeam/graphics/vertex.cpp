#include <moonbeam/graphics/vertex.hpp>

using namespace MoonBeam;
using namespace Graphics;

Vertex Vertex::CreateVertex(glm::vec4 point, glm::vec2 uv, glm::vec3 normal) {
  Vertex output;
  output.point = point;
  output.uv = uv;
  output.normal = normal;
  return output;
}

bool Vertex::operator==(const Vertex& other) const {
  return (point == other.point && normal == other.normal && uv == other.uv);
}

bool Vertex::operator!=(const Vertex& other) const {
  return !(*this == other);
}
