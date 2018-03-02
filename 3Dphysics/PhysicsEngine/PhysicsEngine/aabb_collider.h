#pragma once
#ifndef AABB_COLLIDER_H
#define AABB_COLLIDER_H

#include <glm/glm.hpp>
#include "collider.h"

class AABBCollider : public Collider
{
public:
  AABBCollider(const glm::vec3 h_e, const glm::vec3 p)
  {
    pos = p;
    type = ColliderType::AABBType;

    half_ext = glm::abs(h_e);
    aabb_max = pos + half_ext;
    aabb_min = pos - (aabb_max - pos);
  }

  glm::vec3& GetHalf() { return half_ext; }
  const glm::vec3 GetMin() const { return aabb_min; }
  const glm::vec3 GetMax() const { return aabb_max; }

  void UpdateCollider(Transform t)
  {
    pos = t.GetPos();
    aabb_max = pos + half_ext;
    aabb_min = pos - (aabb_max - pos);
  }

private:
  glm::vec3 half_ext;
	glm::vec3 aabb_min;
	glm::vec3 aabb_max;
};

#endif
