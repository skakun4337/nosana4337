#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <moonbeam/dependencies.hpp>
#include <moonbeam/core/component-manager.hpp>

namespace MoonBeam {
  namespace Core {
    class Entity {
    public:
      Entity();
      virtual ~Entity();

      EntityId GetEntityId() const;
      bool IsActive() const;

      void SetActive(bool state);

      virtual void OnEnable();
      virtual void OnDisable();

      template <class T>
      T* AddComponent() {
        return this->_comp_manager->CreateComponent<T>(this->GetEntityId());
      }

      template <class T>
      void RemoveComponent() {
        this->_comp_manager->DestroyComponent<T>(this->GetEntityId());
      }

      template <class T>
      T* GetComponent() {
        this->_comp_manager->GetComponent<T>(this->GetEntityId());
      }

      bool operator==(const Entity& other) const;
      bool operator!=(const Entity& other) const;

      friend class EntityManager;

    protected:

    private:
      EntityId _id;
      bool _active;

      ComponentManager* _comp_manager;
      EntityManager* _ent_manager;

    };
  }
}
#endif