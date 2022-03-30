#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

namespace MoonBeam {
  namespace Core{
    namespace Memory {
      class Allocator;
      class LinearAllocator;
      class StackAllocator;
      class BlockListAllocator;
      template <class T> class PoolAllocator;
      class ProxyAllocator;
    }

    namespace Container {
      template <class T> class IdMap;
      template <class T> class FixedSet;
      template <class T, class K> class FixedUnorderedMap;
    }

    class Exception;

    typedef size_t TypeId;

    class SystemManager;
    typedef TypeId SystemId;
    class System;

    class EntityManager;
    typedef unsigned long EntityId;
    class Entity;

    class ComponentManager;
    typedef unsigned long ComponentId;
    class Component;
    typedef std::unordered_map<ComponentId, Component*>::iterator ComponentIterator;
  }

  class Transform;

  namespace Graphics {
    class GLObject;
    class Window;

    typedef unsigned long TextureId;
    class Texture;
    class Texture2D;

    typedef unsigned long ShaderId;
    class Shader;
    class DrawShader;
    class ComputeShader;

    typedef unsigned long MaterialId;
    class Material;
    class ComputeMaterial;

    typedef unsigned long MeshId;
    struct Vertex;
    class Mesh;

    class Model;

    class Camera;

    struct TransfMatrices {
      glm::mat4 view;
      glm::mat4 projection;
    };

    class GraphicSystem;
  }

  class MoonBeamEngine;
}
#endif
