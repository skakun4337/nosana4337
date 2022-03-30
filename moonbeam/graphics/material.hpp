#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <moonbeam/dependencies.hpp>
#include <map>

namespace MoonBeam { namespace Graphics {
class Material {
public:
  Material();
  virtual ~Material();

  ShaderId GetShader() const;
  
  void SetShader(const ShaderId& shader);
  void SetTexture(unsigned int index, const TextureId& tex);

  const std::map<unsigned int, TextureId>& GetTexutres() const;

private:
  ShaderId _shader;
  std::map<unsigned int, TextureId> _textures;
};
}}

#endif
