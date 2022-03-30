#ifndef MOONBEAM_TRANFORM_HPP
#define MOONBEAM_TRANFORM_HPP

#include <moonbeam/dependencies.hpp>
#include <moonbeam/core/component.hpp>

namespace MoonBeam{
class Transform : public Core::Component {
public:
  Transform();
  ~Transform() override;

  glm::vec3 GetPosition() const;
  glm::vec3 GetRotation() const;
  glm::vec3 GetScale() const;

  void SetPosition(const glm::vec3& pos);
  void SetRotation(const glm::vec3& rot);
  void SetScale(const glm::vec3& scale);

  glm::mat4 GetTrasformMatrix() const;

private:
  glm::vec3 _position;
  glm::vec3 _rotation;
  glm::vec3 _scale;
};
}
#endif