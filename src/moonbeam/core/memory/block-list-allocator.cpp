#include <moonbeam/core/memory/block-list-allocator.hpp>

using namespace MoonBeam;
using namespace Core;
using namespace Memory;

BlockListAllocator::BlockListAllocator(void* start, size_t size) : Allocator(start, size), _free_blocks((FreeBlock*)start) {
  assert(size > sizeof(FreeBlock));
  new (_free_blocks) FreeBlock();
  _free_blocks->size = size; 
  _free_blocks->next = nullptr; 
}

BlockListAllocator::~BlockListAllocator() {
  _free_blocks = nullptr; 
}

void* BlockListAllocator::AllocateMemory(size_t size, u_int8_t alignment) {
  assert(size != 0 && alignment != 0); 
  FreeBlock* prev_free_block = nullptr; 
  FreeBlock* free_block = _free_blocks; 
  
  while(free_block != nullptr)   {
    //Calculate adjustment needed to keep object correctly aligned 
    u_int8_t adjustment = this->AlignForwardAdjustmentWithHeader(free_block, alignment, sizeof(AllocationHeader)); 
    size_t total_size = size + adjustment; 
    
    //If allocation doesn't fit in this FreeBlock, try the next 
    if(free_block->size < total_size) {
      prev_free_block = free_block; 
      free_block = free_block->next; 
      continue;
    } 
    
    static_assert(sizeof(AllocationHeader) >= sizeof(FreeBlock), "sizeof(AllocationHeader) < sizeof(FreeBlock)"); 
    
    //If allocations in the remaining memory will be impossible 
    if(free_block->size - total_size <= sizeof(AllocationHeader)) {
      //Increase allocation size instead of creating a new FreeBlock 
      total_size = free_block->size; 
      
      if(prev_free_block != nullptr) 
        prev_free_block->next = free_block->next; 
      else 
        _free_blocks = free_block->next; 
    } else {
      //Else create a new FreeBlock containing remaining memory 
      FreeBlock* next_block = (FreeBlock*)( this->Add(free_block, total_size) );
      
      next_block->size = free_block->size - total_size;
      next_block->next = free_block->next; 
      
      if(prev_free_block != nullptr) 
        prev_free_block->next = next_block; 
      else 
        _free_blocks = next_block;
    } 
    
    uintptr_t aligned_address = (uintptr_t)free_block + adjustment; 
    AllocationHeader* header = (AllocationHeader*)(aligned_address - sizeof(AllocationHeader)); 
    header->size = total_size; 
    header->adjustment = adjustment; 
    _used += total_size; 
    _number_allocated++; 
    
    assert(this->AlignForwardAdjustment((void*)aligned_address, alignment) == 0); 
    
    return (void*)aligned_address; 
  } 
  
  //assert(false && "Couldn't find free block large enough!"); 
  return nullptr; 
}

void BlockListAllocator::DeallocateMemory(void* p) 
{
  assert(p != nullptr); 
  AllocationHeader* header = (AllocationHeader*)this->Subtract(p, sizeof(AllocationHeader)); 
  uintptr_t block_start = reinterpret_cast<uintptr_t>(p) - header->adjustment; 
  size_t block_size = header->size; 
  uintptr_t block_end = block_start + block_size; 
  FreeBlock* prev_free_block = nullptr; 
  FreeBlock* free_block = _free_blocks; 
  
  while(free_block != nullptr)  {
    if( (uintptr_t) free_block >= block_end ) 
      break; 
    prev_free_block = free_block; 
    free_block = free_block->next;
  }
  
  if(prev_free_block == nullptr) {
    prev_free_block = (FreeBlock*) block_start; 
    prev_free_block->size = block_size; 
    prev_free_block->next = _free_blocks; 
    _free_blocks = prev_free_block; 
  } else if((uintptr_t) prev_free_block + prev_free_block->size == block_start) {
    prev_free_block->size += block_size; 
  } else {
    FreeBlock* temp = (FreeBlock*) block_start; 
    temp->size = block_size; 
    temp->next = prev_free_block->next; 
    prev_free_block->next = temp; 
    prev_free_block = temp; 
  }
  
  if( free_block != nullptr && (uintptr_t) free_block == block_end) {
    prev_free_block->size += free_block->size; 
    prev_free_block->next = free_block->next;
  }
  
  _number_allocated--; 
  _used -= block_size; 
}

void* BlockListAllocator::GetCurrentPosition() {
  return this->_free_blocks->next;
}
