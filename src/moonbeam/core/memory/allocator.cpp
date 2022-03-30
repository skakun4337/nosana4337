#include <moonbeam/core/memory/allocator.hpp>

using namespace MoonBeam;
using namespace Core;
using namespace Memory;

Allocator::Allocator(void* start, size_t size) {
  this->_start = start;
  this->_size = size;
  this->_used = 0;
  this->_number_allocated = 0;
}

Allocator::~Allocator() {
  assert(_used == 0 && _number_allocated == 0);
  _start = nullptr;
  _size = 0;
}

void* Allocator::GetStart() const {
  return this->_start;
}

size_t Allocator::GetSize() const {
  return this->_size;
}
size_t Allocator::GetUsedMemory() const {
  return this->_used;
}

size_t Allocator::GetNumberAllocations() const {
  return this->_number_allocated;
}

void Allocator::Clear() {}

bool Allocator::IsAligned(void* address, u_int8_t alignment) {
  return this->AlignForward(address, alignment) == 0;
}

void* Allocator::AlignForward(void* address, u_int8_t alignment) {
  return (void*)( ( reinterpret_cast<uintptr_t>(address) + static_cast<u_int8_t>(alignment-1) ) & static_cast<u_int8_t>(~(alignment-1)) );
}

u_int8_t Allocator::AlignForwardAdjustment(const void* address, u_int8_t alignment) { 
  u_int8_t adjustment = alignment - (reinterpret_cast<uintptr_t>(address) & static_cast<uintptr_t>(alignment-1)); 
  
  if(adjustment == alignment) return 0; 
  
  //already aligned 
  return adjustment; 
} 

u_int8_t Allocator::AlignForwardAdjustmentWithHeader(const void* address, u_int8_t alignment, u_int8_t headerSize) 
{
  u_int8_t adjustment = this->AlignForwardAdjustment(address, alignment); 
  u_int8_t neededSpace = headerSize; 
  // printf("address: %p\n", address);
  // printf("headerSize: %d\n", headerSize);
  // printf("pre-adjustment: %d\n", adjustment);
  
  if(adjustment < neededSpace) 
  {
    neededSpace -= adjustment; 
    
    //Increase adjustment to fit header 
    adjustment += alignment * (neededSpace / alignment); 
    
    if(neededSpace % alignment > 0) adjustment += alignment;
  }
  // printf("adjustment: %d\n", adjustment);
  return adjustment; 
}

void* Allocator::Add(void* pointer, size_t x) {
  return (void*)(reinterpret_cast<uintptr_t>(pointer)+x);
}

void* Allocator::Subtract(void* pointer, size_t x) {
  return (void*)(reinterpret_cast<uintptr_t>(pointer)-x);
}
