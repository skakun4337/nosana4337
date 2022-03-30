namespace MoonBeam { namespace Graphics {
template <class T>
Buffer<T>::Buffer(T* data) {}

template <class T>
Buffer<T>::~Buffer() {}

template <class T>
void Buffer<T>::Bind() {
  glBindBuffer(this->GetGLType(), this->GetGLId());
}

template <class T>
void Buffer<T>::UnBind() {
  glBindBuffer(this->GetGLType(), 0);
}

template <class T>
template <class K>
void Buffer<T>::SetSubData(K* data, unsigned long offset) {
  this->Bind();
  glBufferSubData(this->GetGLType(), offset, sizeof(*data), data);
}

template <class T>
T* Buffer<T>::GetData() {
  return this->_data;
}
}}
