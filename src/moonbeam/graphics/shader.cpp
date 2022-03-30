#include <moonbeam/graphics/shader.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

#include <moonbeam/core/exception.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace MoonBeam;
using namespace Graphics;

Shader::Shader() {}

Shader::~Shader() {
  //glDeleteProgram(this->GetGLId());
}

void Shader::Bind() {
  glUseProgram(this->GetGLId());
}

void Shader::SetBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(this->GetGLId(), name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(this->GetGLId(), name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(this->GetGLId(), name.c_str()), value);
}

void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const {
  glUniform2fv(glGetUniformLocation(this->GetGLId(), name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const {
  glUniform3fv(glGetUniformLocation(this->GetGLId(), name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const {
  glUniform4fv(glGetUniformLocation(this->GetGLId(), name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &value) const {
  glUniformMatrix4fv(glGetUniformLocation(this->GetGLId(), name.c_str()), 1, GL_FALSE, glm::value_ptr(value));//&value[0][0]);
}

void Shader::BindUniformBlock(const std::string &name, int point) {
  glUniformBlockBinding(this->GetGLId(), glGetUniformBlockIndex(this->GetGLId(), name.c_str()), point);
}

void Shader::CheckCompileErrors(unsigned int shader, std::string type) {
  int success;
  char infoLog[1024];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
    std::stringstream message;
    message << "Shader Compilation Error: \n" << type << "\n" << infoLog;
    throw Core::Exception(message.str());
  }
}

void Shader::CheckLinkErrors(unsigned int program) {
  int success;
  char infoLog[1024];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 1024, NULL, infoLog);
    std::stringstream message;
    message << "Shader Linking Error:\n" << infoLog;
    throw Core::Exception(message.str());
  }
}

std::string* Shader::LoadShaderCode(const char* path) {
  std::string *code;
  try {
    std::ifstream file;
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    file.open(path);
    std::stringstream stream;
    stream << file.rdbuf();
    file.close();
    code = new std::string(stream.str());
  } catch (std::ifstream::failure e) {
    std::stringstream message;
    message << "Shader file not successfully read:\n" << path;
    throw Core::Exception(message.str());
  }
  return code;
}
