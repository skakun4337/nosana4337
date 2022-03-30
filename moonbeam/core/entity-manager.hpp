#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <moonbeam/dependencies.hpp>

#include <moonbeam/core/utils/utils.hpp>
#include <moonbeam/core/memory/pool-allocator.hpp>
#include <moonbeam/core/container/id-map.hpp>
#include <moonbeam/core/entity.hpp>

#include <map>
#include <unordered_map>

namespace MoonBeam {
  namespace Core {
    class EntityManager {
    public:
      EntityManager(Memory::Allocator* main, size_t mapSize, unsigned int maxEntities);
      ~EntityManager();

      void SetComponentManager(ComponentManager* compManager);
      ComponentManager* GetComponentManager() const;

      template <class T>
      T* CreateEntity() {
        TypeId tid = Utils::GetTypeId<T>();
        auto iter = _type_allocators.find(tid);
        Memory::Allocator* alloc;
        if (iter == _type_allocators.end()) {
          alloc = _main_allocator->AllocateAllocator<Memory::PoolAllocator<T>>(_map_size);
          assert(alloc != nullptr);

          _type_allocators[tid] = alloc;

        } else {
          alloc = iter->second;
        }

        T* ent = alloc->Allocate<T>();

        assert(ent != nullptr);
        
        ent->_id = this->GetNextId();
        ent->_comp_manager = this->GetComponentManager();
        ent->_ent_manager = this;
        _entities[ent->_id] = ent;
        return ent;
      }

      Entity* GetEntity(const EntityId& id);
      void DestroyEntity(const EntityId& id);

      EntityManager(const EntityManager&) = delete;
      EntityManager& operator=(EntityManager&) = delete;

    private:
      Memory::Allocator* _main_allocator;
      std::map<TypeId, Memory::Allocator*> _type_allocators;
      std::unordered_map<EntityId, Entity*> _entities;

      Container::IdMap<EntityId>* _id_map;
      EntityId GetNextId();
      void FreeId(const EntityId& id);

      size_t _map_size;

      ComponentManager* _comp_manager;
    };
  }
}
#endif
