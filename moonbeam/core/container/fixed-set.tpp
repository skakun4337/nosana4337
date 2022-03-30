namespace MoonBeam { namespace Core { namespace Container {
template <class T>
FixedSet<T>::FixedSet(Memory::Allocator* allocator, unsigned int size) {
  this->_allocator = allocator;
  this->_size = size;

  this->_set = _allocator->AllocateArray<T*>(size);
  size_t poolSize = Memory::PoolAllocator<T>::GetSizeForNumber(size);
  this->_pool = _allocator->AllocateAllocator<Memory::PoolAllocator<T>>(poolSize);
}  

template <class T>
FixedSet<T>::~FixedSet() {}

template <class T>
unsigned int FixedSet<T>::MaxSize() {
  return this->_size;
}

template <class T>
unsigned int FixedSet<T>::Size() {
  return this->_pool->GetNumberAllocations();
}

template <class T>
unsigned int FixedSet<T>::Insert(T&& element) {
  if (this->Size() == this->MaxSize())
    return -1;
  T* p = this->_pool->Allocate(std::forward<T>(element));
  this->_set[this->Size() -1] = p;
  return this->Size() -1;
}

template <class T>
void FixedSet<T>::Erase(T&& element) {
  unsigned int index = this->Find(std::forward<T>(element));
  if (index == -1) return;
  this->_pool->Dealocate(std::forward<T>(element));
  this->_set[index] = nullptr;
  this->CompactSet();
}

template <class T>
void FixedSet<T>::Erase(unsigned int index) {
  if (index < 0 || index >= _size) return;
  this->_pool->Dealocate(std::forward<T>(this->_set[index]));
  this->_set[index] = nullptr;
  this->CompactSet();
}

template <class T>
void FixedSet<T>::Erase(unsigned int min, unsigned int max) {
  for (unsigned int i = min; i <= max; i++)
    this->Erase(i);
}

template <class T>
void FixedSet<T>::Empty() {
  this->Erase(0, this->Size()-1);
}

template <class T>
unsigned int FixedSet<T>::Find(T&& element) {
  for (unsigned int i = 0; i < _size; i++) {
    if (*_set[i] == element)
      return i;
  }
  return -1;
}

template <class T>
void FixedSet<T>::CompactSet() {
  for (unsigned int i = 0; i < _size; i++) {
    if (_set[i] == nullptr) {
      for (unsigned int j = i+1; j < _size; j++) {
        _set[j-1] = _set[j];
      }
    }
  }
}


template <class T>
T& FixedSet<T>::operator[](unsigned int index) const {
  return *this->_set[index];
}

}}}
