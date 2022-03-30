#include <moonbeam/core/system.hpp>

using namespace MoonBeam;
using namespace Core;

System::System(Memory::LinearAllocator* allocator) {
  this->_allocator = allocator;
}

System::~System() {}

void System::SetActive(bool state) {
  this->_active = state;
}

bool System::IsActive() const {
  return this->_active;
}

Memory::LinearAllocator* System::GetAllocator() {
  return this->_allocator;
}

ComponentManager* System::GetComponentManager() {
  return this->_comp_manager;
}

SystemManager* System::GetSystemManager() {
  return this->_sys_manager;
}