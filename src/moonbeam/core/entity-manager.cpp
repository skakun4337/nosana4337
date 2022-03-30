#include <moonbeam/core/entity-manager.hpp>

using namespace MoonBeam;
using namespace Core;

EntityManager::EntityManager(Memory::Allocator* main, size_t mapSize, unsigned int maxEntities) {
  this->_main_allocator = main;
  this->_map_size = mapSize;

  this->_id_map = main->Allocate<Container::IdMap<EntityId>>(maxEntities, main);
}

EntityManager::~EntityManager() {
  _main_allocator->Clear();
  _map_size = 0;
}

void EntityManager::SetComponentManager(ComponentManager* comManager) {
  this->_comp_manager = comManager;
}

ComponentManager* EntityManager::GetComponentManager() const {
  return this->_comp_manager;
}

Entity* EntityManager::GetEntity(const EntityId& id) {
  auto iter = _entities.find(id);
  if (iter == _entities.end())
    return nullptr;
  else
    return iter->second;
}

void EntityManager::DestroyEntity(const EntityId& id) {
  Entity* ent = GetEntity(id);
  if (ent != nullptr) {
    TypeId tid = Utils::GetTypeId(*ent);
    _type_allocators[tid]->Dealocate(*ent);
    this->_id_map->FreeId(id);
    this->_entities.erase(id);
  }
}

EntityId EntityManager::GetNextId() {
  return this->_id_map->OccupyId();
}

void EntityManager::FreeId(const EntityId& id) {
  this->_id_map->FreeId(id);
}