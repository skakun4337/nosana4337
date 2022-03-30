#include <moonbeam/graphics/graphic-system.hpp>
#include <moonbeam/core/exception.hpp>
#include <moonbeam/core/memory/linear-allocator.hpp>
#include <moonbeam/core/container/fixed-unordered-map.hpp>
#include <moonbeam/core/component-manager.hpp>
#include <moonbeam/transform.hpp>
#include <moonbeam/graphics/draw-shader.hpp>
#include <moonbeam/graphics/compute-shader.hpp>
#include <moonbeam/graphics/texture2d.hpp>
#include <moonbeam/graphics/material.hpp>
#include <moonbeam/graphics/mesh.hpp>
#include <moonbeam/graphics/model.hpp>
#include <moonbeam/graphics/compute-material.hpp>
#include <moonbeam/graphics/camera.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

using namespace MoonBeam;
using namespace Graphics;

using Core::Container::FixedUnorderedMap;

GraphicSystem::GraphicSystem(Core::Memory::LinearAllocator* allocator) : System(allocator),  _matrices_buffer(&this->_matrices, 0) {
  //TODO: max items in configuration
  this->_draw_shaders = GetAllocator()->Allocate<FixedUnorderedMap<ShaderId, DrawShader>>(GetAllocator(), 200);
  this->_comp_shaders = GetAllocator()->Allocate<FixedUnorderedMap<ShaderId, ComputeShader>>(GetAllocator(), 100);
  this->_textures = GetAllocator()->Allocate<FixedUnorderedMap<TextureId, Texture*>>(GetAllocator(), 300);
  this->_textures_2d = GetAllocator()->Allocate<FixedUnorderedMap<TextureId, Texture2D>>(GetAllocator(), 100);
  this->_materials = GetAllocator()->Allocate<FixedUnorderedMap<MaterialId, Material>>(GetAllocator(), 100);

}

GraphicSystem::~GraphicSystem() {}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void GraphicSystem::SetMainCamera(Camera* cam) {
  if (cam != nullptr)
    this->_main_camera = cam;
}

Camera* GraphicSystem::GetMainCamera() const {
  return this->_main_camera;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

ShaderId GraphicSystem::LoadDrawShader(const char* vertexPath, const char* fragmentPath) {
  ShaderId id = GetShaderId();
  this->_draw_shaders->Insert(id, DrawShader());
  try {
    (*this->_draw_shaders)[id].Load(vertexPath, fragmentPath);
  } catch(Core::Exception& e) {
    std::cout << e.what() << std::endl;
    exit(-1);
  }
  (*this->_draw_shaders)[id].BindUniformBlock("Matrices", 0);
  return id;
}
// DrawShader* GraphicSystem::GetDrawShader(const ShaderId& id) {
// 
// }

void GraphicSystem::DestroyDrawShader(const ShaderId& id) {
  this->_draw_shaders->Erase(id);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

ShaderId GraphicSystem::LoadComputeShader(const std::string& filepath) {
  ShaderId id = GetShaderId();
  this->_comp_shaders->Insert(id, ComputeShader());
  try {
    (*this->_comp_shaders)[id].Load(filepath);
  } catch(Core::Exception& e) {
    std::cout << e.what() << std::endl;
    exit(-1);
  }
  return id;
}
// ComputeShader* GraphicSystem::GetComputeShader(const ShaderId& id);
void GraphicSystem::DestroyComputeShader(const ShaderId& id) {
  this->_comp_shaders->Erase(id);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TextureId GraphicSystem::LoadTexture2D(const std::string& filepath) {
  TextureId id = GetTextureId();
  try {
    this->_textures_2d->Insert(id, Texture2D(filepath));
    this->_textures->Insert(id, &(*this->_textures_2d)[id]);
  } catch (Core::Exception& e) {
    std::cout << e.what() << std::endl;
    exit(-1);
  }
  return id;
}
TextureId GraphicSystem::CreateTexture2D(unsigned int width, unsigned int height) {
  TextureId id = GetTextureId();
  this->_textures_2d->Insert(id, Texture2D(width, height));
  this->_textures->Insert(id, &(*this->_textures_2d)[id]);
  return id;
}
// Texture* GraphicSystem::GetTexture(const TextureId& id);
// void GraphicSystem::DestroyTexture(const TextureId& id) {

// }

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

MaterialId GraphicSystem::CreateMaterial() {
  MaterialId id = GetMaterialId();
  this->_materials->Insert(id, Material());
  return id;
}

void GraphicSystem::DestroyMaterial(const MaterialId& id) {
  this->_materials->Erase(id);
}

void GraphicSystem::BindTextureToMaterial(const MaterialId& mid, const TextureId& tid, unsigned int index) {
  (*this->_materials)[mid].SetTexture(index, tid);
}

void GraphicSystem::BindShaderToMaterial(const MaterialId& mid, const ShaderId& sid) {
  (*this->_materials)[mid].SetShader(sid);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void GraphicSystem::PreUpdate() {

}

void GraphicSystem::Update() {

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  this->UpdateUniforms();

  IterateOnComponents<Model>([this](Model* mod) {
    Material* m = &(*this->_materials)[mod->GetMaterial()];
    ShaderId sid = m->GetShader();
    Shader* s = &(*this->_draw_shaders)[sid];
    s->Bind();
    Transform* t = GetComponentManager()->GetComponent<Transform>(mod->GetEntityId());
    s->SetMat4("model", t->GetTrasformMatrix());
    std::for_each(m->GetTexutres().begin(), m->GetTexutres().end(), [this](auto p) {
      glActiveTexture(p.first);
      (*this->_textures)[p.second]->Bind();
    });

    mod->GetMesh()->Draw();
  });

  
}

void GraphicSystem::PostUpdate() {
  
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void GraphicSystem::UpdateUniforms() {
  this->_matrices.view = glm::lookAt(_main_camera->GetPosition(), _main_camera->GetTarget(), _main_camera->GetUp());
  this->_matrices.projection = glm::perspective(glm::radians(_main_camera->GetFOW()), _main_camera->GetRatio(), _main_camera->GetNear(), _main_camera->GetFar());
  _matrices_buffer.SetSubData(&(_matrices.view), 0);
  _matrices_buffer.SetSubData(&(_matrices.projection), sizeof(glm::mat4));
}

ShaderId GraphicSystem::GetShaderId() {
  static ShaderId id = 0;
  return id++;
}

TextureId GraphicSystem::GetTextureId() {
  static TextureId id = 0;
  return id++;
}

MaterialId GraphicSystem::GetMaterialId() {
  static MaterialId id = 0;
  return id++;
}
