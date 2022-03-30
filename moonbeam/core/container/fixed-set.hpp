#ifndef MOONBEAM_CORE_CONTAINER_FIXED_SET_HPP
#define MOONBEAM_CORE_CONTAINER_FIXED_SET_HPP

#include <moonbeam/dependencies.hpp>
#include <moonbeam/core/memory/pool-allocator.hpp>

namespace MoonBeam { namespace Core { namespace Container {
template <class T>
class FixedSet {
public:
  FixedSet(Memory::Allocator* allocator, unsigned int size);
  ~FixedSet();

  unsigned int MaxSize();
  unsigned int Size();

  unsigned int Insert(T&& element);
  
  void Erase(T&& element);
  void Erase(unsigned int index);
  void Erase(unsigned int min, unsigned int max);

  void Empty();

  unsigned int Find(T&& element);

  T& operator[](unsigned int index) const;

protected:

private:
  Memory::Allocator* _allocator;
  Memory::PoolAllocator<T>* _pool;

  unsigned int _size;
  T** _set;

  void CompactSet();
};

}}}

#include <moonbeam/core/container/fixed-set.tpp>

#endif