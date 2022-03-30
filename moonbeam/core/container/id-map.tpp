namespace MoonBeam { namespace Core { namespace Container {
template <class T>
IdMap<T>::IdMap(unsigned int size, Memory::Allocator* allocator) {
  this->_size = size;
  this->_number_occupied = 0;
  
  this->_map = allocator->AllocateArray<Block>(size);
  for (unsigned int i = 0; i < size; i++) {
    this->_map[i].id = (T)i;
    this->_map[i].occupied = false;
  }
  this->_next_free = 0;

  this->_allocator = allocator;
}

template <class T>
IdMap<T>::~IdMap() {
  this->_allocator->DeallocateArray(this->_map);
}

template <class T>
T IdMap<T>::OccupyId() {
//  if(this->_next_free == this->_size)
//    throw Excepition
  unsigned int i = this->_next_free;
  this->_number_occupied++;
  this->_map[i].occupied = true;
  this->_next_free = this->GetNextFree();
  return this->_map[i].id;
}

template <class T>
void IdMap<T>::FreeId(const T& id) {
  for(unsigned int i = 0; i < this->_size; i++) {
    if (this->_map[i].id == id) {
      this->_next_free = i;
      this->_number_occupied--;
      this->_map[i].occupied = false;
    }
  }
}

template <class T>
unsigned int IdMap<T>::GetSize() const {
  return this->_size;
}

template <class T>
unsigned int IdMap<T>::GetNumberOccupied() const {
  return this->_number_occupied;
}

template <class T>
unsigned int IdMap<T>::GetNumberFree() const {
  return this->GetSize() - this->GetNumberOccupied();
}

template <class T>
unsigned int IdMap<T>::GetNextFree() {
  for (unsigned int i = 0; i < this->_size; i++) {
    if (!(this->_map[i].occupied)) {
      return i;
    }
  }
  return this->_size;
}
}}}
