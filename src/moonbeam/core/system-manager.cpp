#include <moonbeam/core/system-manager.hpp>
#include <queue>
#include <moonbeam/core/system.hpp>

using namespace MoonBeam;
using namespace Core;

SystemManager::SystemManager(Memory::Allocator* main, size_t systemMemory) {
  this->_main_allocator = main;
  this->_system_memory = systemMemory;
}

SystemManager::~SystemManager() {
  this->_main_allocator->Clear();
}

void SystemManager::SetComponentManager(ComponentManager* comManager) {
  this->_comp_manager = comManager;
}

ComponentManager* SystemManager::GetComponentManager() const {
  return this->_comp_manager;
}

void SystemManager::Update() {
  for (unsigned int i = 0; i < this->_execution_order.size(); i++) {
    this->_execution_order[i]->PreUpdate();
  }
  for (unsigned int i = 0; i < this->_execution_order.size(); i++) {
    this->_execution_order[i]->Update();
  }
  for (unsigned int i = 0; i < this->_execution_order.size(); i++) {
    this->_execution_order[i]->PostUpdate();
  }
}

void SystemManager::SortSystems() {
  this->_execution_order.clear();
  std::unordered_map<System*, int> indegree;
  for (auto iter = this->_systems.begin(); iter != this->_systems.end(); iter++)
    indegree[iter->second] = 0;
  for (auto iter1 = this->_dependecy_map.begin(); iter1 != this->_dependecy_map.end(); iter1++) {
    for (auto iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++) {
      indegree[*iter2] += 1;
    }
  }

  std::queue<System*> q;

  for (auto iter = this->_systems.begin(); iter != this->_systems.end(); iter++)
    if (indegree[iter->second] == 0)
      q.push(iter->second);

  unsigned int count = 0;

  while(!q.empty()) {
    System* s = q.front();
    q.pop();
    this->_execution_order.push_back(s);

    for (auto iter = this->_dependecy_map[s].begin(); iter != this->_dependecy_map[s].end(); iter++) {
      indegree[*iter]--;
      if  (indegree[*iter] == 0)
        q.push(*iter);
    }
    count++;
  }

  assert(count == this->_systems.size());
}