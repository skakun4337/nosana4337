#ifndef MOONBEAM_GRAPHIC_SYSTEM_HPP
#define MOONBEAM_GRAPHIC_SYSTEM_HPP

#include <moonbeam/dependencies.hpp>
#include <moonbeam/core/system.hpp>
#include <moonbeam/graphics/uniform-buffer.hpp>

namespace MoonBeam { namespace Graphics {
class GraphicSystem : public MoonBeam::Core::System {
public:
  GraphicSystem(Core::Memory::LinearAllocator* allocator);
  ~GraphicSystem() override;

  void SetMainCamera(Camera* cam);
  Camera* GetMainCamera() const;

  ShaderId LoadDrawShader(const char* vertexPath, const char* fragmentPath);
  DrawShader* GetDrawShader(const ShaderId& id);
  void DestroyDrawShader(const ShaderId& id);

  ShaderId LoadComputeShader(const std::string& filepath);
  ComputeShader* GetComputeShader(const ShaderId& id);
  void DestroyComputeShader(const ShaderId& id);

  TextureId LoadTexture2D(const std::string& filepath);
  TextureId CreateTexture2D(unsigned int width, unsigned int height);
  Texture* GetTexture(const TextureId& id);
  void DestroyTexture(const TextureId& id);

  MaterialId CreateMaterial();
  void DestroyMaterial(const MaterialId& id);
  void BindTextureToMaterial(const MaterialId& mid, const TextureId& tid, unsigned int index);
  void BindShaderToMaterial(const MaterialId& mid, const ShaderId& sid);

  void PreUpdate() override;
  void Update() override;
  void PostUpdate() override;

private:
  Camera* _main_camera;

  Core::Container::FixedUnorderedMap<ShaderId, void*>* _shaders;
  Core::Container::FixedUnorderedMap<ShaderId, DrawShader>* _draw_shaders;
  Core::Container::FixedUnorderedMap<ShaderId, ComputeShader>* _comp_shaders;
  Core::Container::FixedUnorderedMap<TextureId, Texture*>* _textures;
  Core::Container::FixedUnorderedMap<TextureId, Texture2D>* _textures_2d;
  Core::Container::FixedUnorderedMap<MaterialId, Material>* _materials;

  UniformBuffer<TransfMatrices> _matrices_buffer;
  TransfMatrices _matrices;

  void UpdateUniforms();
  
  ShaderId GetShaderId();
  TextureId GetTextureId();
  MaterialId GetMaterialId();
};
}}

#endif
