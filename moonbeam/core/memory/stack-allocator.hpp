#ifndef STACK_ALLOCATOR_HPP
#define STACK_ALLOCATOR_HPP

#include <moonbeam/dependencies.hpp>
#include <moonbeam/core/memory/allocator.hpp>

namespace MoonBeam { namespace Core { namespace Memory {
class StackAllocator : public Allocator {
public:
  StackAllocator(void* start, size_t size);
  virtual ~StackAllocator();
  void Clear() override;
private:
  StackAllocator(const StackAllocator&);
  StackAllocator& operator=(const StackAllocator&);

  struct AllocationHeader {
    void* prev_address; 
    u_int8_t adjustment;
  };
  
  void* _prev_position;  
  void* _position;
  
  void* AllocateMemory(size_t size, u_int8_t alignment = 4) override;
  void DeallocateMemory(void* pointer) override;
  void DeallocateMemory();

  void* GetCurrentPosition() override;
};
}}}

#endif
