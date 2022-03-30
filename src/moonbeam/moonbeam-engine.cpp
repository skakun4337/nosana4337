#include <moonbeam/moonbeam-engine.hpp>

#include <moonbeam/core/exception.hpp>

#include <moonbeam/core/memory/linear-allocator.hpp>
#include <moonbeam/core/memory/proxy-allocator.hpp>

#include <moonbeam/core/system-manager.hpp>
#include <moonbeam/core/entity-manager.hpp>
#include <moonbeam/core/component-manager.hpp>

#include <moonbeam/graphics/window.hpp>

using namespace MoonBeam;

MoonBeamEngine::MoonBeamEngine() {
  size_t size = this->ComputeGlobalMemorySize();
  this->_memory = malloc(size + 128*1024);
  this->_main_allocator = new Core::Memory::LinearAllocator(this->_memory, size + 128*1024);

  this->_sys_alloc = _main_allocator->AllocateAllocator<Core::Memory::LinearAllocator>(size/3);
  this->_sys_proxy = _main_allocator->Allocate<Core::Memory::ProxyAllocator>(*this->_sys_alloc);
  this->_sys_manager = new Core::SystemManager(this->_sys_proxy, size/30);
  
  this->_ent_alloc = _main_allocator->AllocateAllocator<Core::Memory::LinearAllocator>(size/3);
  this->_ent_proxy = _main_allocator->Allocate<Core::Memory::ProxyAllocator>(*this->_ent_alloc);
  this->_ent_manager = new Core::EntityManager(this->_ent_proxy, 4096, 10000);

  this->_comp_alloc = _main_allocator->AllocateAllocator<Core::Memory::LinearAllocator>(size/3);
  this->_comp_proxy = _main_allocator->Allocate<Core::Memory::ProxyAllocator>(*this->_comp_alloc);
  this->_comp_manager = new Core::ComponentManager(this->_comp_proxy, 64*1024, 10000);

  this->_sys_manager->SetComponentManager(this->_comp_manager);
  this->_ent_manager->SetComponentManager(this->_comp_manager);
  this->_comp_manager->SetEntityManager(this->_ent_manager);
}

MoonBeamEngine::~MoonBeamEngine() {
  this->_main_allocator->Clear();
  delete this->_main_allocator;
  free(this->_memory);
}

Core::SystemManager* MoonBeamEngine::GetSystemManager() const {
  return this->_sys_manager;
}

Core::EntityManager* MoonBeamEngine::GetEntityManager() const {
  return this->_ent_manager;
}

Core::ComponentManager* MoonBeamEngine::GetComponentManager() const {
  return this->_comp_manager;
}

Graphics::Window* MoonBeamEngine::CreateWindow(unsigned int width, unsigned int height) {
  this->_window = _main_allocator->Allocate<Graphics::Window>(width, height);
  try {
    this->_window->Open();
  } catch (Core::Exception& e) {
    std::cout << e.what() << std::endl;
    exit(-1);
  }
  return this->_window;
}

size_t MoonBeamEngine::ComputeGlobalMemorySize() {
  //TODO
  return 3*1024*1024*sizeof(u_int8_t);
}
