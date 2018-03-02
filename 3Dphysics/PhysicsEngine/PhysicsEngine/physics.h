#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

#include "sphere_collider.h"
#include "aabb_collider.h"
#include "plane_collider.h"
#include "cylinder_collider.h"
#include "entity.h"
#include <vector>

enum IntersectionType
{
  Inside,
  Outside,
  Coplanar,
  NUM_OF_INTERSECTIONTYPES
};

typedef bool (*FuncType)(const Collider*, const Collider*);

IntersectionType PointPlane(glm::vec3 a, const PlaneCollider b, float epsilon);

bool SphereSphere(const Collider* a, const Collider* b);
bool SphereAABB(const Collider* a, const Collider* b);
bool SpherePlane(const Collider* a, const Collider* b);
bool AABBPlane(const Collider* a, const Collider* b);
bool AABBAABB(const Collider* a, const Collider* b);
bool CylinderSphere(const Collider* a, const Collider* b);
bool CylinderAABB(const Collider* a, const Collider* b);
bool CylinderPlane(const Collider* a, const Collider* b);
bool CylinderCylinder(const Collider* a, const Collider* b);

void Physics_Update(std::vector<Entity*>& entity_list);

#endif // !PHYSICS_H

