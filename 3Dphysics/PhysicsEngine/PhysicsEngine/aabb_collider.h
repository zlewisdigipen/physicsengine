#pragma once
#ifndef AABB_COLLIDER_H
#define AABB_COLLIDER_H

#include <glm/glm.hpp>
#include "collider.h"

class AABBCollider : public Collider
{
public:
  AABBCollider(const glm::vec3 h_e)
  {
    type = ColliderType::AABBType;

    half_ext = glm::abs(h_e);

    rig = Rigibody();
  }

  glm::vec3& GetHalf() { return half_ext; }
  const glm::vec3 GetMin() const { return aabb_min; }
  const glm::vec3 GetMax() const { return aabb_max; }

  void UpdateCollider(Transform* t)
  {
    tran = t;
    aabb_max = t->GetPos() + half_ext;
    aabb_min = t->GetPos() - (aabb_max - t->GetPos());
  }

private:
  glm::vec3 half_ext;
	glm::vec3 aabb_min;
	glm::vec3 aabb_max;
};

#endif
