#ifndef MOONBEAM_CORE_CONTAINER_FIXED_UNORDERED_MAP_HPP
#define MOONBEAM_CORE_CONTAINER_FIXED_UNORDERED_MAP_HPP

#include <moonbeam/dependencies.hpp>
#include <moonbeam/core/memory/pool-allocator.hpp>

namespace MoonBeam { namespace Core { namespace Container {
template <class K, class V>
class FixedUnorderedMap {
public:
  FixedUnorderedMap(Memory::Allocator* allocator, unsigned int size);
  ~FixedUnorderedMap();

  unsigned int MaxSize();
  unsigned int Size();

  unsigned int Insert(const K& key, const V& value);
  // unsigned int Insert(const K& key);
  
  void Erase(const K& key);
  void Erase(unsigned int index);
  void Erase(unsigned int min, unsigned int max);

  void Empty();

  unsigned int Find(const K& key);

  V& operator[](const K& key);

protected:

private:
  class pair_type {
  public:
    K key;
    V value;
    pair_type() {}
    pair_type(const K& key, const V& value) {
      this->key = key;
      this->value = value;
    }
  };

  Memory::Allocator* _allocator;
  Memory::PoolAllocator<pair_type>* _pool;

  unsigned int _size;
  pair_type** _map;

  void CompactMap();
};
}}}

#include <moonbeam/core/container/fixed-unordered-map.tpp>

#endif
