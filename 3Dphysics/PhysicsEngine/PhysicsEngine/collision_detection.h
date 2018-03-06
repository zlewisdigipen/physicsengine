#pragma once
#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "sphere_collider.h"
#include "aabb_collider.h"
#include "plane_collider.h"
#include "cylinder_collider.h"

enum IntersectionType
{
  Inside,
  Outside,
  Coplanar,
  NUM_OF_INTERSECTIONTYPES
};

IntersectionType PointPlane(glm::vec3 a, const PlaneCollider b, float epsilon);

bool CD_SphereSphere(const Collider* a, const Collider* b);
bool CD_SphereAABB(const Collider* a, const Collider* b);
bool CD_SpherePlane(const Collider* a, const Collider* b);
bool CD_AABBPlane(const Collider* a, const Collider* b);
bool CD_AABBAABB(const Collider* a, const Collider* b);
bool CD_CylinderSphere(const Collider* a, const Collider* b);
bool CD_CylinderAABB(const Collider* a, const Collider* b);
bool CD_CylinderPlane(const Collider* a, const Collider* b);
bool CD_CylinderCylinder(const Collider* a, const Collider* b);

#endif // !COLLISION_DETECTION_H

