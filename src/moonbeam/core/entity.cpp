#include <moonbeam/core/entity.hpp>

using namespace MoonBeam;
using namespace Core;

Entity::Entity() {}

Entity::~Entity() {}

EntityId Entity::GetEntityId() const {
  return this->_id;
}

bool Entity::IsActive() const {
  return this->_active;
}

void Entity::SetActive(bool state) {
  if(this->_active != state) {
    this->_active = state;
    if(state) {
      this->OnEnable();
    } else {
      this->OnDisable();
    }
  }
}

bool Entity::operator==(const Entity& other) const {
  return this->_id == other._id;
}

bool Entity::operator!=(const Entity& other) const {
  return !(*this == other);
}

void Entity::OnEnable() {}

void Entity::OnDisable() {}
