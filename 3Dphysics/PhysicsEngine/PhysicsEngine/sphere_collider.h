#pragma once
#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

#include <glm/glm.hpp>
#include "collider.h"

class SphereCollider: public Collider
{
public:
	SphereCollider(const float r): radius(r) 
  { 
    type = ColliderType::SphereType; 
  }

	const float GetRadius() const { return radius; }

  void UpdateCollider(Transform* t) { tran = t; }

private:
	const float radius;
};

#endif // !BOUNDING_SPHERE_H
