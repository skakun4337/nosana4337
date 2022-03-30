#ifndef UNIFORM_BUFFER_HPP
#define UNIFORM_BUFFER_HPP

#include <moonbeam/graphics/buffer.hpp>

namespace MoonBeam { namespace Graphics {
template<class T>
class UniformBuffer : public Buffer<T> {
public:
  UniformBuffer(T* data, int point);
  virtual ~UniformBuffer();
};
}}

#include <moonbeam/graphics/uniform-buffer.tpp>

#endif