#pragma once
#ifndef COLLIDER_H
#define COLLIDER_H

#include "transform.h"

enum ColliderType
{
	SphereType,
	AABBType,
  CylinderType,
	PlaneType,
	NumberOfColliderType
};

class Collider
{
public:
	Collider() {}
	//Collider(const ColliderType t) : type(t) {}

	const ColliderType GetType() const { return type; }
  glm::vec3& GetPos() { return pos; }

  virtual void UpdateCollider(Transform t) {}

protected:
	ColliderType type;
  glm::vec3 pos;
};

#endif