#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <moonbeam/dependencies.hpp>
#include <moonbeam/graphics/gl-object.hpp>

namespace MoonBeam { namespace Graphics {
class Texture : public GLObject {
public:
  Texture();
  Texture(int width, int height);
  virtual ~Texture();

  int GetWidth() const;
  int GetHeight() const;

  virtual void Bind() = 0;

protected:
  int _width;
  int _height;

  std::string _filepath;
};
}}

#endif
