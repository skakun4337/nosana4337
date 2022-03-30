namespace MoonBeam { namespace Graphics {
template <class T>
UniformBuffer<T>::UniformBuffer(T* data, int point) : Buffer<T>(data){
  this->SetGLType(GL_UNIFORM_BUFFER);
  glGenBuffers(1, this->RefGLId());
  this->Bind();
  glBufferData(this->GetGLType(), sizeof(*data), data, GL_STATIC_DRAW);
  this->UnBind();
  glBindBufferRange(this->GetGLType(), point, this->GetGLId(), 0, sizeof(*data));
  this->_data = data;//(T*)glMapBufferRange(this->_type, 0, sizeof(*data), GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
}

template <class T>
UniformBuffer<T>::~UniformBuffer() {
  // glDeleteBuffers(this->_id);
}

}}
