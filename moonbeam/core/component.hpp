#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <moonbeam/dependencies.hpp>

namespace MoonBeam {
  namespace Core {
    class Component {
    public:
      Component();
      virtual ~Component();

      ComponentId GetComponentId() const;
      EntityId GetEntityId() const;

      bool operator==(const Component& other) const;
      bool operator!=(const Component& other) const;

      friend class ComponentManager;
    protected:

      ComponentManager* GetComponentManager();
      EntityManager* GetEntityManager();

    private:
      ComponentId _id;
      EntityId _eid;

      ComponentManager* _comp_manager;
      EntityManager* _ent_manager;
    };
  }
}
#endif