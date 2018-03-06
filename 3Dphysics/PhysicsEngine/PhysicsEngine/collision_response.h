#pragma once
#ifndef COLLISION_RESPONSE_H
#define COLLISION_RESPONSE_H

#include "sphere_collider.h"
#include "aabb_collider.h"
#include "plane_collider.h"
#include "cylinder_collider.h"

void CR_SpherePlane(const Collider* a, const Collider* b);
void CR_AABBPlane(const Collider* a, const Collider* b);
void CR_AABBAABB(const Collider* a, const Collider* b);
void CR_CylinderSphere(const Collider* a, const Collider* b);
void CR_CylinderAABB(const Collider* a, const Collider* b);
void CR_CylinderPlane(const Collider* a, const Collider* b);
void CR_CylinderCylinder(const Collider* a, const Collider* b);
void CR_SphereSphere(const Collider* a, const Collider* b);
void CR_SphereAABB(const Collider* a, const Collider* b);

#endif // !COLLISION_RESPONSE_H
