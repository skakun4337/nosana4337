#ifndef UTILS_HPP
#define UTILS_HPP

#include <moonbeam/dependencies.hpp>

namespace MoonBeam {
  namespace Core {

    namespace Utils {
      template <class T>
      TypeId GetTypeId() {
        return (TypeId)typeid(T).hash_code();
      }

      template <class T>
      TypeId GetTypeId(const T& t) {
        return (TypeId)typeid(t).hash_code();
      }
    }
  }
}

#endif
