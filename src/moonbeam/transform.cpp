#include <moonbeam/transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

using namespace MoonBeam;

Transform::Transform() : _position(0.0f, 0.0f, 0.0f), _rotation(0.0f, 0.0f, 0.0f), _scale(1.0f, 1.0f, 1.0f) {}

Transform::~Transform() {}

glm::vec3 Transform::GetPosition() const {
  return this->_position;
}

glm::vec3 Transform::GetRotation() const {
  return this->_rotation;
}

glm::vec3 Transform::GetScale() const {
  return this->_scale;
}

void Transform::SetPosition(const glm::vec3& pos) {
  this->_position = pos;
}

void Transform::SetRotation(const glm::vec3& rot) {
  this->_rotation = rot;
}

void Transform::SetScale(const glm::vec3& scale) {
  this->_scale = scale;
}

glm::mat4 Transform::GetTrasformMatrix() const {
  glm::mat4 mat(1);
  mat = glm::translate(mat, GetPosition());
  mat *= glm::eulerAngleXYZ(GetRotation().x, GetRotation().y, GetRotation().z);
  mat = glm::scale(mat, GetScale());
  return mat;
}