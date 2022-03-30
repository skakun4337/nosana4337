#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <moonbeam/dependencies.hpp>
#include <moonbeam/graphics/gl-object.hpp>

namespace MoonBeam { namespace Graphics {
template <class T>
class Buffer : public GLObject{
public:
  Buffer(T* data);
  virtual ~Buffer();

  virtual void Bind();
  virtual void UnBind();
  template <class K>
  void SetSubData(K* data, unsigned long offset);

  T* GetData();
protected:
  T* _data;
};
}}

#include <moonbeam/graphics/buffer.tpp>

#endif
