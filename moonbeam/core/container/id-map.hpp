#ifndef ID_MAP_HPP
#define ID_MAP_HPP

#include <moonbeam/dependencies.hpp>

namespace MoonBeam { namespace Core { namespace Container {
template <class T>
class IdMap {
public:
  IdMap(unsigned int size, Memory::Allocator* allocator);
  ~IdMap();

  T OccupyId();
  void FreeId(const T& id);

  unsigned int GetSize() const;
  unsigned int GetNumberOccupied() const;
  unsigned int GetNumberFree() const;
private:
  struct Block {
    bool occupied;
    T id;
  };

  Block* _map;
  unsigned int _next_free;
  unsigned int _size;
  unsigned int _number_occupied;
  unsigned int GetNextFree();

  Memory::Allocator* _allocator;
};
}}}

#include <moonbeam/core/container/id-map.tpp>

#endif
