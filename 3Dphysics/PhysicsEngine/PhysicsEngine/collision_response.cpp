#include "collision_response.h"

void CR_SpherePlane(const Collider* c1, const Collider* c2)
{
  SphereCollider* a = (SphereCollider*)(c1);
  PlaneCollider* b = (PlaneCollider*)(c2);

  glm::vec3 reflected = 2.0f * b->GetNormal() * (glm::dot(b->GetNormal(), (a->GetRigibody().GetDirection())));
  a->GetRigibody().GetDirection() -= reflected;
}

void CR_AABBPlane(const Collider* c1, const Collider* c2)
{

}

void CR_CylinderPlane(const Collider* c1, const Collider* c2)
{

}

void CR_SphereAABB(const Collider* c1, const Collider* c2)
{

}

void CR_CylinderSphere(const Collider* c1, const Collider* c2)
{

}

void CR_CylinderAABB(const Collider* c1, const Collider* c2)
{

}

void CR_CylinderCylinder(const Collider* c1, const Collider* c2)
{

}

void CR_SphereSphere(const Collider* c1, const Collider* c2)
{

}

void CR_AABBAABB(const Collider* c1, const Collider* c2)
{

}

void  CR_PlanePlane(const Collider* c1, const Collider* c2)
{

}
