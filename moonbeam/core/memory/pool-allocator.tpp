namespace MoonBeam { namespace Core { namespace Memory {

template <class T>
PoolAllocator<T>::PoolAllocator(void* start, size_t size) : Allocator(start, size) {
  this->_alignment = alignof(Block);
  this->_block_size = sizeof(Block);

  uint8_t adjustment = this->AlignForwardAdjustment(start, _alignment);
  void* block = this->Add(start, adjustment);
  size_t numObjects = (size-adjustment)/this->_block_size;
  this->_first_free = block;
  new (block) Block();
  ((Block*)block)->occupied = false;

  //Initialize free blocks list 
  for(size_t i = 0; i < numObjects; i++) {
    new (block) Block();
    ((Block*)block)->occupied = false;
    block = this->Add(block, this->_block_size);
  }
}

template <class T>
PoolAllocator<T>::~PoolAllocator() {
  _first_free = nullptr;
}

template <class T>
void PoolAllocator<T>::Clear() {
  this->_used = 0;
  this->_number_allocated = 0;
  uint8_t adjustment = this->AlignForwardAdjustment(_start, _alignment);
  void* block = this->Add(_start, adjustment);
  size_t numObjects = (_size-adjustment)/this->_block_size;
  for(size_t i = 0; i < numObjects; i++) {
    ((Block*)block)->occupied = false;
  }
}

template <class T>
size_t PoolAllocator<T>::GetBlockSize() {
  return sizeof(Block);
}

template <class T>
u_int8_t PoolAllocator<T>::GetBlockAlignment() {
  return alignof(Block);
}

template <class T>
size_t PoolAllocator<T>::GetSizeForNumber(unsigned int number) {
  return PoolAllocator<T>::GetBlockSize() * number;
}

template <class T>
void* PoolAllocator<T>::AllocateMemory(size_t size, u_int8_t alignment) {
  assert(PoolAllocator<T>::GetBlockSize() == _block_size && PoolAllocator<T>::GetBlockAlignment() == _alignment); 
  if(_first_free == nullptr) 
    return nullptr;
  
  void* p = _first_free;
  ((Block*)_first_free)->occupied = true;
  _first_free = this->NextFree();
  _used += _block_size;
  _number_allocated++; 
  return &((Block*)p)->data; 
}

template <class T>
void PoolAllocator<T>::DeallocateMemory(void* p) {
  p = this->Subtract(p, 4);
  _first_free = p;
  ((Block*)p)->occupied = false;
  _used -= this->_block_size; 
  _number_allocated--;
}

template <class T>
void* PoolAllocator<T>::NextFree() {
  uint8_t adjustment = this->AlignForwardAdjustment(_start, _alignment);
  void* block = this->Add(_start, adjustment);
  size_t numObjects = (_size-adjustment)/this->_block_size;
  
  for(size_t i = 0; i < numObjects; i++) {
    if (!((Block*)block)->occupied)
      return block;
    block = this->Add(block, this->_block_size);
  }

  return nullptr;
}

template <class T>
void* PoolAllocator<T>::GetCurrentPosition() {
  return nullptr;
}

}}}
