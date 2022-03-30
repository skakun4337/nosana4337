#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <moonbeam/dependencies.hpp>
#include <moonbeam/core/component.hpp>

namespace MoonBeam { namespace Graphics {
class Camera : public MoonBeam::Core::Component {
public:
  Camera();
  ~Camera() override;

  void SetPosition(glm::vec3& pos);
  void SetUp(glm::vec3& up);
  void SetTarget(glm::vec3& target);
  void SetFOW(float fow);
  void SetRatio(float ratio);
  void SetRatio(unsigned int width, unsigned int height);
  void SetNear(float near);
  void SetFar(float far);

  glm::vec3 GetPosition();
  glm::vec3 GetUp();
  glm::vec3 GetTarget();
  float GetFOW();
  float GetRatio();
  float GetNear();
  float GetFar();

  void SetActive();
  void Deactivate();

private:
  glm::vec3 _up;
  glm::vec3 _target;

  Transform* _transform;

  float _fow;
  float _ratio;
  float _near;
  float _far;
  
  void GetTransform();

};
}}

#endif