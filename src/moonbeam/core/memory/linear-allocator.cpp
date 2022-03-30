#include <moonbeam/core/memory/linear-allocator.hpp>

using namespace MoonBeam;
using namespace Core;
using namespace Memory;

LinearAllocator::LinearAllocator(void* start, size_t size) : Allocator(start, size) {
  assert(size > 0);
  this->_position = start;
}

LinearAllocator::~LinearAllocator() {
  this->_position = nullptr;
}

void* LinearAllocator::AllocateMemory(size_t size, u_int8_t alignment) {
  assert(size != 0);
  u_int8_t adjustment = this->AlignForwardAdjustment(_position, alignment); 
  
  if(this->_used + adjustment + size > _size) return nullptr; 
  
  uintptr_t aligned_address = (uintptr_t)(this->_position) + adjustment; 
  this->_position = (void*)(aligned_address + size); 
  this->_used += size + adjustment; 
  this->_number_allocated++; 
  
  return (void*)aligned_address;
}

void LinearAllocator::DeallocateMemory(void* pointer) {
  assert( false && "Use clear() instead" );
}

void LinearAllocator::Clear() {
  this->_number_allocated = 0; 
  this->_used = 0;
  this->_position = _start;
} 

void* LinearAllocator::GetCurrentPosition() {
  return this->_position;
}