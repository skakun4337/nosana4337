#include <moonbeam/core/component.hpp>

using namespace MoonBeam;
using namespace Core;

Component::Component() {}

Component::~Component() {}

ComponentId Component::GetComponentId() const {
  return this->_id;
}

EntityId Component::GetEntityId() const {
  return this->_eid;
}

bool Component::operator==(const Component& other) const {
  return (this->_id == other._id) && (this->_eid == other._eid);
}

bool Component::operator!=(const Component& other) const {
  return !(*this == other);
}

ComponentManager* Component::GetComponentManager() {
  return this->_comp_manager;
}

EntityManager* Component::GetEntityManager() {
  return this->_ent_manager;
}
