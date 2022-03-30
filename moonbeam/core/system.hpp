#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <moonbeam/dependencies.hpp>
#include <moonbeam/core/system-manager.hpp>
#include <moonbeam/core/component-manager.hpp>

namespace MoonBeam {
  namespace Core {
    class System {
    public:
      System(Memory::LinearAllocator* allocator);
      virtual ~System();

      virtual void PreUpdate() = 0;
      virtual void Update() = 0;
      virtual void PostUpdate() = 0;

      void SetActive(bool state);
      bool IsActive() const;

      template <class ...T>
      void AddDependencies(T&& ...dependencies) {
        this->_sys_manager->AddDependencies(this, std::forward<T>(dependencies)...);
      }
      
      friend class SystemManager;

    protected:
      template <class T, typename F>
      void IterateOnComponents(F function) {
        this->_comp_manager->IterateOnComponents<T>(function);
      }

      Memory::LinearAllocator* GetAllocator();

      ComponentManager* GetComponentManager();
      SystemManager* GetSystemManager();

    private:
      SystemId _id;

      bool operator==(const System& other) const;
      bool operator!=(const System& other) const;
      System(const System& other);

      bool _active;

      ComponentManager* _comp_manager;
      SystemManager* _sys_manager;

      Memory::LinearAllocator* _allocator;
    };
  }
}

#endif
