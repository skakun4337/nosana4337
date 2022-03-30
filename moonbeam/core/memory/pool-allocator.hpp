#ifndef POOL_ALLOCATOR_HPP
#define POOL_ALLOCATOR_HPP

#include <moonbeam/dependencies.hpp>
#include <moonbeam/core/memory/allocator.hpp>

namespace MoonBeam { namespace Core { namespace Memory {
template <class T>
class PoolAllocator : public Allocator {
public:
  PoolAllocator(void* start, size_t size);
  virtual ~PoolAllocator();
  void Clear() override;

  static size_t GetBlockSize();
  static u_int8_t GetBlockAlignment();
  static size_t GetSizeForNumber(unsigned int number);
private:
  PoolAllocator(const PoolAllocator&);
  PoolAllocator& operator=(const PoolAllocator&);

  struct Block {
    bool occupied;
    T data;
  };

  size_t _block_size;
  uint8_t _alignment;
  void* _first_free;
  
  void* AllocateMemory(size_t size, u_int8_t allignment = 4) override;
  void DeallocateMemory(void* pointer) override;

  void* NextFree();
  void* GetCurrentPosition() override;
};
}}}

#include <moonbeam/core/memory/pool-allocator.tpp>

#endif
