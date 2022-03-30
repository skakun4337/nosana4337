#include <moonbeam/core/memory/proxy-allocator.hpp>

using namespace MoonBeam;
using namespace Core;
using namespace Memory;

ProxyAllocator::ProxyAllocator(Allocator& allocator) : Allocator(allocator.GetStart(), allocator.GetSize()), _allocator(allocator) {}

ProxyAllocator::~ProxyAllocator() {}

void* ProxyAllocator::AllocateMemory(size_t size, u_int8_t alignment) {
  assert(size != 0);

  _number_allocated++;
  void* p = _allocator.AllocateMemory(size, alignment);
  _used = _allocator.GetUsedMemory();
  return p;
}

void ProxyAllocator::DeallocateMemory(void* pointer) {
  _number_allocated--;
  _allocator.DeallocateMemory(pointer);
  _used = _allocator.GetUsedMemory();
}

void* ProxyAllocator::GetCurrentPosition() {
  return _allocator.GetCurrentPosition();
}