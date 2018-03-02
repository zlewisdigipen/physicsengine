#pragma once
#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

#include <glm/glm.hpp>
#include "collider.h"

class SphereCollider: public Collider
{
public:
	SphereCollider(const glm::vec3 c, const float r): radius(r) 
  { 
    pos = c;
    type = ColliderType::SphereType; 
  }

	const float GetRadius() const { return radius; }

  void UpdateCollider(Transform t) { pos = t.GetPos(); }

private:
	const float radius;
};

#endif // !BOUNDING_SPHERE_H
