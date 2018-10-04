#pragma once
#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "sphere_collider.h"
#include "aabb_collider.h"
#include "plane_collider.h"
#include "cylinder_collider.h"

typedef struct
{
  glm::vec3 normal;
  glm::vec3 contact_point;
  float pen_depth;
}Contact;

typedef struct
{
  const Collider* c1;
  const Collider* c2;
  unsigned contact_count;
  Contact contacts[2];
}Manifold;

enum IntersectionType
{
  Inside,
  Outside,
  Coplanar,
  NUM_OF_INTERSECTIONTYPES
};

IntersectionType PointPlane(glm::vec3 a, const PlaneCollider b, float epsilon);

Manifold CD_SphereSphere(const Collider* a, const Collider* b);
Manifold CD_SphereAABB(const Collider* a, const Collider* b);
Manifold CD_SpherePlane(const Collider* a, const Collider* b);
Manifold CD_AABBPlane(const Collider* a, const Collider* b);
Manifold CD_AABBAABB(const Collider* a, const Collider* b);
Manifold CD_CylinderSphere(const Collider* a, const Collider* b);
Manifold CD_CylinderAABB(const Collider* a, const Collider* b);
Manifold CD_CylinderPlane(const Collider* a, const Collider* b);
Manifold CD_CylinderCylinder(const Collider* a, const Collider* b);
Manifold CD_PlanePlane(const Collider* a, const Collider* b);

#endif // !COLLISION_DETECTION_H

