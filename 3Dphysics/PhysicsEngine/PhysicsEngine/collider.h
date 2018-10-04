#pragma once
#ifndef COLLIDER_H
#define COLLIDER_H

#include "transform.h"
#include "rigidbody.h"

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
	Collider() { colliding = false; }
	//Collider(const ColliderType t) : type(t) {}
    virtual ~Collider() {}

	const ColliderType GetType() const { return type; }
    Transform* GetTransform() { return tran; }
    Rigibody& GetRigibody() { return rig; }

	bool colliding;

  virtual void UpdateCollider(Transform* t) {}

protected:
	ColliderType type;
    Transform* tran;
    Rigibody rig;
};

#endif