#ifndef LINEAR_ALLOCATOR_HPP
#define LINEAR_ALLOCATOR_HPP

#include <moonbeam/dependencies.hpp>
#include <moonbeam/core/memory/allocator.hpp>

namespace MoonBeam { namespace Core { namespace Memory {
class LinearAllocator : public Allocator {
public:
  LinearAllocator(void* start, size_t size);
  virtual ~LinearAllocator();
  void Clear() override;
private:
  LinearAllocator(const LinearAllocator&);
  LinearAllocator& operator=(const LinearAllocator&);

  void* _position;
  
  void* AllocateMemory(size_t size, u_int8_t alignment = 4) override;
  void DeallocateMemory(void* pointer) override;
  void* GetCurrentPosition() override;
};
}}}

#endif
