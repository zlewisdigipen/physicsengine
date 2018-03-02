#pragma once
#ifndef CYLINDER_COLLIDER_H
#define CYLINDER_COLLIDER_H

#include "collider.h"

class CylinderCollider : public Collider
{
public:
  CylinderCollider(glm::vec3 p, const float h, const float r) : height(h), radius(r)
  {
    type = ColliderType::CylinderType;
    pos = p;
  }

  const float GetRadius() const { return radius; }
  const float GetHeight() const { return height; }

  void UpdateCollider(Transform t) { pos = t.GetPos(); }

private:
  const float height;
  const float radius;
};

#endif // !CYLINDER_COLLIDER_H
