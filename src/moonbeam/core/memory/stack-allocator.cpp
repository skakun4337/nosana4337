#include <moonbeam/core/memory/stack-allocator.hpp>

using namespace MoonBeam;
using namespace Core;
using namespace Memory;

StackAllocator::StackAllocator(void* start, size_t size) : Allocator(start, size) {
  assert(size > 0); 
  this->_prev_position = nullptr; 
  this->_position = start;
}

StackAllocator::~StackAllocator() {
  _prev_position = nullptr;
    
  _position = nullptr; 
}

void StackAllocator::Clear() {
  this->_position = this->_start;
  this->_used = 0;
  this->_number_allocated = 0;
}

void* StackAllocator::AllocateMemory(size_t size, u_int8_t alignment) {
  assert(size != 0); 
  u_int8_t adjustment = this->AlignForwardAdjustmentWithHeader(_position, alignment, sizeof(AllocationHeader)); 
  
  if(_used + adjustment + size > _size) return nullptr; 
  
  void* aligned_address = this->Add(_position, adjustment); 
   
  //Add Allocation Header
  AllocationHeader* header = (AllocationHeader*)(this->Subtract(aligned_address, sizeof(AllocationHeader)));
  
  new (header) AllocationHeader();
  header->adjustment = adjustment;
  header->prev_address = _prev_position;
  _prev_position = aligned_address; 
  
  _position = this->Add(aligned_address, size); 
  _used += size + adjustment; 
  _number_allocated++; 
  
  return aligned_address; 
}

void StackAllocator::DeallocateMemory(void* pointer) {
  assert(pointer ==  _prev_position);
  this->DeallocateMemory();
}

void StackAllocator::DeallocateMemory() {
  AllocationHeader* header = (AllocationHeader*)(this->Subtract(_prev_position, sizeof(AllocationHeader))); 
  _used -= (uintptr_t)_position - (uintptr_t)_prev_position + header->adjustment; 
  _position = this->Subtract(_prev_position, header->adjustment); 
  _prev_position = header->prev_address;
  _number_allocated--; 
}

void* StackAllocator::GetCurrentPosition() {
  return this->_position;
}
