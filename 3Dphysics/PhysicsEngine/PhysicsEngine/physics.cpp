#include "physics.h"
#include <iostream>

FuncType detection_lookup[ColliderType::NumberOfColliderType][ColliderType::NumberOfColliderType] = {{ SphereSphere, SphereAABB, SpherePlane },
                                                                                                     { SphereAABB,   AABBAABB,   AABBPlane },
                                                                                                     { SpherePlane,  AABBPlane,  0 }};

void Physics_Update(std::vector<Entity> entity_list)
{
  //Update transforms
  for (unsigned i = 0; i < entity_list.size(); i++)
    entity_list[i].GetCollider()->UpdateCollider(entity_list[i].GetTransform());

  //Collision Detection and update colliders
  for (unsigned i = 0; i < entity_list.size(); i++)
  {
    for (unsigned j = i + 1; j < entity_list.size(); j++)
    {
      const Collider* c1 = entity_list[i].GetCollider();
      const Collider* c2 = entity_list[j].GetCollider();

      if (c1->GetType() < c2->GetType())
      {
        if (detection_lookup[c1->GetType()][c2->GetType()](c1, c2))
          std::cout << "Colliding" << std::endl;

      }
      else
      {
        if (detection_lookup[c1->GetType()][c2->GetType()](c2, c1))
          std::cout << "Colliding" << std::endl;
      }
    }
  }
}

bool SphereSphere(const Collider* c1, const Collider* c2)
{
  SphereCollider* a = (SphereCollider*)(c1);
  SphereCollider* b = (SphereCollider*)(c2);

  glm::vec3 temp = a->GetPos() - b->GetPos();
  float rad = a->GetRadius() + b->GetRadius();


  if (glm::dot(temp, temp) - (rad * rad) <= 0)
    return true;

  return false;
}

bool SphereAABB(const Collider* c1, const Collider* c2)
{
  SphereCollider* a = (SphereCollider*)(c1);
  AABBCollider* b = (AABBCollider*)(c2);

  auto check = [&](
    const float pn,
    const float bmin,
    const float bmax) -> float
  {
    float out = 0.0f;
    float v = pn;

    if (v < bmin)
    {
      float val = (bmin - v);
      out += val * val;
    }

    if (v > bmax)
    {
      float val = (v - bmax);
      out += val * val;
    }

    return out;
  };

  // Squared distance
  float sq = 0.0f;

  sq += check(a->GetPos().x, b->GetMin().x, b->GetMax().x);
  sq += check(a->GetPos().y, b->GetMin().y, b->GetMax().y);
  sq += check(a->GetPos().z, b->GetMin().z, b->GetMax().z);

  if (sq - (a->GetRadius() * a->GetRadius()) <= 0.0f)
    return true;

  return false;
}


IntersectionType PointPlane(glm::vec3 a, const PlaneCollider b, float epsilon)
{
  //PlaneCollider plane = b.Normalized();
  float dist = glm::dot(glm::vec3(a.x, a.y, a.z), glm::vec3(b.GetNormal().x, b.GetNormal().y, b.GetNormal().z)) - b.GetDistance();

  if (dist > epsilon)
    return IntersectionType::Inside;

  if (dist <= epsilon && dist >= -epsilon)
    return IntersectionType::Coplanar;

  return IntersectionType::Outside;
}

bool SpherePlane(const Collider* c1, const Collider* c2)
{
  SphereCollider* a = (SphereCollider*)(c1);
  PlaneCollider* b = (PlaneCollider*)(c2);

  IntersectionType t = PointPlane(a->GetPos(), *b, a->GetRadius());

  if (t == IntersectionType::Coplanar)
    return true;

  return false;
}

bool AABBPlane(const Collider* c1, const Collider* c2)
{
  AABBCollider* a = (AABBCollider*)(c1);
  PlaneCollider* b = (PlaneCollider*)(c2);

  float x_half = (a->GetMax().x - a->GetMin().x) / 2;
  float y_half = (a->GetMax().y - a->GetMin().y) / 2;
  float z_half = (a->GetMax().z - a->GetMin().z) / 2;

  glm::vec3 center = 0.5f * (a->GetMax() + a->GetMin());

  if (b->GetNormal().x < 0)
    x_half *= -1;
  if (b->GetNormal().y < 0)
    y_half *= -1;
  if (b->GetNormal().z < 0)
    z_half *= -1;

  glm::vec3 furthest_p = center + glm::vec3(x_half, y_half, z_half);
  glm::vec3 nearest_p = center + glm::vec3(-x_half, -y_half, -z_half);

  IntersectionType furthest_val = PointPlane(furthest_p, *b, 0.0f);
  IntersectionType nearest_val = PointPlane(nearest_p, *b, 0.0f);

  if ((furthest_val == IntersectionType::Inside && nearest_val == IntersectionType::Outside) ||
      (furthest_val == IntersectionType::Outside && nearest_val == IntersectionType::Inside) ||
      furthest_val == IntersectionType::Coplanar || nearest_val == IntersectionType::Coplanar)
    return true;

  return false;
}

bool AABBAABB(const Collider* c1, const Collider* c2)
{
  AABBCollider* a = (AABBCollider*)(c1);
  AABBCollider* b = (AABBCollider*)(c2);

  // 6 cases for not intersecting
  if (a->GetMin().x > b->GetMax().x ||
    b->GetMin().x > a->GetMax().x ||
    a->GetMin().y > b->GetMax().y ||
    b->GetMin().y > a->GetMax().y ||
    a->GetMin().z > b->GetMax().z ||
    b->GetMin().z > a->GetMax().z)
  {
    return false;
  }

  return true;
}
