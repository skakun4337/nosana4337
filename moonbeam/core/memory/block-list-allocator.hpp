#ifndef BLOCK_LIST_ALLOCATOR_HPP
#define BLOCK_LIST_ALLOCATOR_HPP

#include <moonbeam/dependencies.hpp>
#include <moonbeam/core/memory/allocator.hpp>

namespace MoonBeam { namespace Core { namespace Memory {
class BlockListAllocator : public Allocator {
public:
  BlockListAllocator(void* start, size_t size);
  virtual ~BlockListAllocator();
  private:
  BlockListAllocator(const BlockListAllocator&);
  BlockListAllocator& operator=(const BlockListAllocator&);

  struct AllocationHeader {
    size_t size;
    u_int8_t adjustment; 
  }; 

  struct FreeBlock {
    size_t size;
    FreeBlock* next;
  };
 
  FreeBlock* _free_blocks;
  
  void* AllocateMemory(size_t size, u_int8_t alignment = 4) override;
  void DeallocateMemory(void* pointer) override;
  void* GetCurrentPosition() override;
};
}}}

#endif