#include <moonbeam/graphics/compute-material.hpp>

using namespace MoonBeam;
using namespace Graphics;

ComputeMaterial::ComputeMaterial() {}

ComputeMaterial::~ComputeMaterial() {}

void ComputeMaterial::Dispatch(bool async) {
  //this->Bind();
  glDispatchCompute(_groupsX, _groupsY, _groupsZ);

  if (!async)
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void ComputeMaterial::SetWorkGroups(unsigned int groupsX,
                                    unsigned int groupsY,
                                    unsigned int groupsZ) {

  if (CheckWorkGroup(groupsX, 0)) this->_groupsX = groupsX;
  if (CheckWorkGroup(groupsY, 1)) this->_groupsY = groupsY;
  if (CheckWorkGroup(groupsZ, 2)) this->_groupsZ = groupsZ;
}

bool ComputeMaterial::CheckWorkGroups(unsigned int groupsX,
                                      unsigned int groupsY,
                                      unsigned int groupsZ) {
  return CheckWorkGroup(groupsX, 0) &&
         CheckWorkGroup(groupsY, 1) &&
         CheckWorkGroup(groupsZ, 2);
}

bool ComputeMaterial::CheckWorkGroup(unsigned int size, int axis) {
  int max;
  glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, axis, &max);
  return size < (unsigned int)max;
}