#include <catch2/catch.hpp>

#include <moonbeam/moonbeam.hpp>

using namespace MoonBeam;
using namespace Core;
using namespace Memory;

TEST_CASE("PoolAllocator", "[Memory::PoolAllocator]") {
  unsigned int memorySize = 1024;
  void* memory = malloc(memorySize * sizeof(u_int8_t));
  PoolAllocator<int> a(memory, memorySize * sizeof(u_int8_t));
  SECTION("Single Variable Allocation") {
    int *i = a.Allocate<int>();
    REQUIRE(i != nullptr);
    *i = 10;
    REQUIRE(*i == 10);

    int *j = a.Allocate<int>(*i);
    REQUIRE(j != nullptr);
    REQUIRE(*j == *i);
    REQUIRE(reinterpret_cast<uintptr_t>(j) == reinterpret_cast<uintptr_t>(i) + static_cast<uintptr_t>(PoolAllocator<int>::GetBlockSize()));

    *i = 0;
    REQUIRE(*j != *i);

    a.Dealocate(*i);
    REQUIRE(i != nullptr);

    int *k = a.Allocate<int>();
    REQUIRE(k == i);

    size_t numberInts = static_cast<size_t>(memorySize * sizeof(u_int8_t)) / sizeof(int) - 2;
    for (size_t ii = 0; ii < numberInts; ii++) {
      a.Allocate<int>();
    }
    REQUIRE(a.GetUsedMemory() == a.GetSize());

    int *w = a.Allocate<int>();
    REQUIRE(w == nullptr); 

    a.Clear();
    REQUIRE(a.GetUsedMemory() == 0);
  }
}