#ifndef MOONBEAM_ENGINE_HPP
#define MOONBEAM_ENGINE_HPP

#include <moonbeam/dependencies.hpp>

namespace MoonBeam{
class MoonBeamEngine {
public:
  MoonBeamEngine();
  ~MoonBeamEngine();

  Core::SystemManager* GetSystemManager() const;
  Core::EntityManager* GetEntityManager() const;
  Core::ComponentManager* GetComponentManager() const;

  Graphics::Window* CreateWindow(unsigned int width, unsigned int height);
private:
  void* _memory;
  Core::Memory::Allocator* _main_allocator;

  Core::SystemManager* _sys_manager;
  Core::Memory::ProxyAllocator* _sys_proxy;
  Core::Memory::LinearAllocator* _sys_alloc;

  Core::EntityManager* _ent_manager;
  Core::Memory::ProxyAllocator* _ent_proxy;
  Core::Memory::LinearAllocator* _ent_alloc;
  
  Core::ComponentManager* _comp_manager;
  Core::Memory::ProxyAllocator* _comp_proxy;
  Core::Memory::LinearAllocator* _comp_alloc;

  Graphics::Window* _window;

  size_t ComputeGlobalMemorySize();
};
}
#endif