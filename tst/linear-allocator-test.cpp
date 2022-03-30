#include <catch2/catch.hpp>

#include <moonbeam/moonbeam.hpp>

using namespace MoonBeam;
using namespace Core;
using namespace Memory;

TEST_CASE("LinearAllocator", "[Memory::LinearAllocator]") {
  unsigned int memorySize = 1024;
  void* memory = malloc(memorySize * sizeof(u_int8_t));
  LinearAllocator a(memory, memorySize * sizeof(u_int8_t));
  SECTION("Single Variable Allocation") {
    int *i = a.Allocate<int>();
    REQUIRE(i != nullptr);
    *i = 10;
    REQUIRE(*i == 10);

    int *j = a.Allocate<int>(*i);
    REQUIRE(j != nullptr);
    REQUIRE(*j == *i);
    REQUIRE(reinterpret_cast<uintptr_t>(j) == reinterpret_cast<uintptr_t>(i) + static_cast<uintptr_t>(sizeof(int)));

    *i = 0;
    REQUIRE(*j != *i);

    size_t numberInts = static_cast<size_t>(memorySize * sizeof(u_int8_t)) / sizeof(int) - 2;
    for (size_t ii = 0; ii < numberInts; ii++) {
      a.Allocate<int>();
    }
    REQUIRE(a.GetUsedMemory() == a.GetSize());

    int *k = a.Allocate<int>();
    REQUIRE(k == nullptr); 

    a.Clear();
    REQUIRE(a.GetUsedMemory() == 0);
  }

  SECTION("Array Allocation") {
    int size = 10;
    uint8_t headerSize = sizeof(size_t)/sizeof(int); 
    if(sizeof(size_t)%sizeof(int) > 0) headerSize += 1; 

    int* array = a.AllocateArray<int>(size);
    REQUIRE(array != nullptr);
    REQUIRE(a.GetUsedMemory() == sizeof(int) * (size + headerSize));
    
    for(int i = 0; i < size; i++) {
      array[i] = i;
      REQUIRE(array[i] == i);
    }

    a.Clear();
    REQUIRE(a.GetUsedMemory() == 0);
    REQUIRE(array != nullptr);
    REQUIRE(array[9] == 9);
  }

  SECTION("Allocate Allocator") {
    int *ii = a.Allocate<int>();
    *ii = 10;
    size_t size = 10 * sizeof(u_int8_t);
    LinearAllocator* b = a.AllocateAllocator<LinearAllocator>(size);
    REQUIRE(*ii == 10);
    REQUIRE(b != nullptr);
    REQUIRE(a.GetUsedMemory() >= sizeof(LinearAllocator) + size);
    
    int *i = b->Allocate<int>();
    REQUIRE(i != nullptr);
    REQUIRE(b->GetUsedMemory() >= sizeof(int));

    *i = 5;
    REQUIRE(*i == 5);

    b->Clear();
    REQUIRE(b->GetUsedMemory() == 0);
    REQUIRE(i != nullptr);
    REQUIRE(*i == 5);

    a.Clear();
    REQUIRE(b != nullptr);
    REQUIRE(a.GetUsedMemory() == 0);
    REQUIRE(*i == 5);
  }
}