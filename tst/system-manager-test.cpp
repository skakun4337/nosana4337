#include <catch2/catch.hpp>

#include <moonbeam/moonbeam.hpp>

using namespace MoonBeam;
using namespace Core;
using namespace Memory;

class S1 : public System {
public:
  S1(LinearAllocator* allocator) : System(allocator) {}
  virtual ~S1() {}
  virtual void PreUpdate() {
    printf("S1 pre-update\n");
  }
  virtual void Update() {
    printf("S1 update\n");
  }
  virtual void PostUpdate() {
    printf("S1 post-update\n");
  }
};

class S2 : public System {
public:
  S2(LinearAllocator* allocator) : System(allocator) {}
  virtual ~S2() {}
  virtual void PreUpdate() {
    printf("S2 pre-update\n");
  }
  virtual void Update() {
    printf("S2 update\n");
  }
  virtual void PostUpdate() {
    printf("S2 post-update\n");
  }
};

TEST_CASE("SystemManager", "[SystemManager]") {
  unsigned int memorySize = 100000;
  void* memory = malloc(memorySize * sizeof(u_int8_t));
  LinearAllocator a(memory, memorySize * sizeof(u_int8_t));
  SystemManager sm(&a, 1024*sizeof(u_int8_t));
  SECTION("System Creation") {
    System* s1 = sm.CreateSystem<S1>();
    REQUIRE(s1 != nullptr);

    a.Clear();
  }

  SECTION("System Dependencies") {
    System* s1 = sm.CreateSystem<S1>();
    REQUIRE(s1 != nullptr);

    System* s2 = sm.CreateSystem<S2>();
    REQUIRE(s2 != nullptr);

    s1->AddDependencies(s2);
    sm.Update();

    a.Clear();
  }
}