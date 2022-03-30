#include <catch2/catch.hpp>

#include <moonbeam/moonbeam.hpp>

using namespace MoonBeam;
using namespace Core;
using namespace Memory;

class E2 : public Entity {
public:
  E2() {}
  virtual ~E2() {}
};

class C2 : public Component {
public:
  C2() {}
  virtual ~C2() {}
};

TEST_CASE("EntityManager", "[EntityManager]") {
  unsigned int memorySize = 100000;
  void* memory = malloc(memorySize * sizeof(u_int8_t));
  LinearAllocator a(memory, memorySize * sizeof(u_int8_t));
  EntityManager em(&a, 1024*sizeof(u_int8_t),10);
  ComponentManager cm(&a, 1024*sizeof(u_int8_t),10);
  SECTION("Entity Creation") {
    Entity* e1 = em.CreateEntity<Entity>();
    REQUIRE(e1 != nullptr);
    REQUIRE(e1->GetEntityId() == 0);

    Entity* e2 = em.GetEntity(e1->GetEntityId());
    REQUIRE(e2 == e1);

    Entity* e3 = em.CreateEntity<Entity>();
    REQUIRE(e3->GetEntityId() == 1);

    em.DestroyEntity(e1->GetEntityId());
    a.Clear();
  }

  SECTION("Multiple Entity Types") {
    Entity* e1 = em.CreateEntity<Entity>();
    REQUIRE(e1 != nullptr);
    REQUIRE(e1->GetEntityId() == 0);

    Entity* e2 = em.CreateEntity<E2>();
    REQUIRE(e2 != nullptr);
    REQUIRE(e2 != e1);
    REQUIRE(e2->GetEntityId() == 1);

    a.Clear();
  }
  
  SECTION("Component Creation") {
    em.SetComponentManager(&cm);

    Entity* e1 = em.CreateEntity<Entity>();
    REQUIRE(e1 != nullptr);
    REQUIRE(e1->GetEntityId() == 0);

    Component* c1 = e1->AddComponent<Component>();
    REQUIRE(c1 != nullptr);
    REQUIRE(c1->GetComponentId() == 0);
    REQUIRE(c1->GetEntityId() == e1->GetEntityId());

    Component* c2 = e1->AddComponent<C2>();
    REQUIRE(c2 != nullptr);
    REQUIRE(c2->GetComponentId() == 1);
    REQUIRE(c2->GetEntityId() == e1->GetEntityId());

    cm.DestroyComponent(c1->GetComponentId());
    REQUIRE(c1 != nullptr);

    Component* c3 = e1->AddComponent<Component>();
    REQUIRE(c3 != nullptr);
    REQUIRE(c3->GetComponentId() == 0);
    REQUIRE(c3->GetEntityId() == e1->GetEntityId());

    e1->RemoveComponent<Component>();
    cm.DestroyComponent<C2>(e1->GetEntityId());

    a.Clear();
  }
}