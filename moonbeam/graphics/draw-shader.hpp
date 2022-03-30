#ifndef DRAW_SHADER_HPP
#define DRAW_SHADER_HPP

#include <moonbeam/graphics/shader.hpp>
#include <string>

namespace MoonBeam { namespace Graphics {
class DrawShader : public Shader {
public:
  DrawShader();
  virtual ~DrawShader();

  void Load(const char* vertexPath, const char* fragmentPath);
};
}}

#endif