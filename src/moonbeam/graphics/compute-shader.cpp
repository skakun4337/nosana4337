#include <moonbeam/graphics/compute-shader.hpp>

using namespace MoonBeam;
using namespace Graphics;

ComputeShader::ComputeShader() : Shader() {}

ComputeShader::~ComputeShader() {}

void ComputeShader::Load(std::string filepath) {
  const char* code = LoadShaderCode(filepath.c_str())->c_str();

  /// TODO: Memory leak up here!

  unsigned int compute = glCreateShader(GL_COMPUTE_SHADER);
  glShaderSource(compute, 1, &code, NULL);
  glCompileShader(compute);
  this->CheckCompileErrors(compute, "Compute");
  
  *(RefGLId()) = glCreateProgram();
  glAttachShader(this->GetGLId(), compute);
  glLinkProgram(this->GetGLId());
  this->CheckLinkErrors(this->GetGLId());
  glDeleteShader(compute);
}