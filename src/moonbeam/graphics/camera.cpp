#include <moonbeam/graphics/camera.hpp>
#include <moonbeam/core/component-manager.hpp>
#include <moonbeam/transform.hpp>

using namespace MoonBeam;
using namespace Graphics;

Camera::Camera() : _up(0.0f, 1.0f, 0.0f), _target(0.0f, 0.0f, 0.0f) {
  this->_near = 0.1f;
  this->_fow = 45.0f;
  this->_far = 50.0f;
  this->_ratio = 800.0f/600.0f;
}

Camera::~Camera() {}

void Camera::SetPosition(glm::vec3& pos) {
  GetTransform();
  _transform->SetPosition(pos);
}

void Camera::SetUp(glm::vec3& up) {
  this->_up = up;
}

void Camera::SetTarget(glm::vec3& target) {
  this->_target = target;
}

void Camera::SetFOW(float fow) {
  this->_fow = fow;
}

void Camera::SetRatio(float ratio) {
  this->_ratio = ratio;
}

void Camera::SetRatio(unsigned int width, unsigned int height) {
  this->SetRatio((float)width/(float)height);
}

void Camera::SetNear(float near) {
  this->_near = near;
}

void Camera::SetFar(float far) {
  this->_far = far;
}

glm::vec3 Camera::GetPosition() {
  GetTransform();
  return _transform->GetPosition();
}

glm::vec3 Camera::GetUp() {
  return this->_up;
}

glm::vec3 Camera::GetTarget() {
  return this->_target;
}

float Camera::GetFOW() {
  return this->_fow;
}

float Camera::GetRatio() {
  return this->_ratio;
}
float Camera::GetNear() {
  return this->_near;
}

float Camera::GetFar() {
  return this->_far;
}

void Camera::SetActive() {
  ///TODO
}

void Camera::Deactivate() {
  ///TODO
}

void Camera::GetTransform() {
  this->_transform = GetComponentManager()->GetComponent<Transform>(GetEntityId());
}
