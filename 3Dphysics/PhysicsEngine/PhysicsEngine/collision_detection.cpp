#include "collision_detection.h"

//Manifold Done
Manifold CD_SphereSphere(const Collider* c1, const Collider* c2)
{
  Manifold m;
  m.contact_count = 0;
  SphereCollider* a = (SphereCollider*)(c1);
  SphereCollider* b = (SphereCollider*)(c2);

  m.c1 = c1;
  m.c2 = c2;

  glm::vec3 t = a->GetTransform()->GetPos() - b->GetTransform()->GetPos();
  float rad = a->GetRadius() + b->GetRadius();


  if (glm::dot(t, t) > (rad * rad))
  {
    m.contact_count = 0;
    return m; //false
  }

  float d = glm::length(t);

  //If they are on top of eachother
  if (d == 0.0f)
  {
    m.contacts[0].pen_depth = a->GetRadius();
    m.contacts[0].normal = glm::vec3(1.0f, 0.0f, 0.0f);
    m.contacts[0].contact_point = a->GetTransform()->GetPos();
    m.contact_count = 1;
  }
  else
  {
    m.contacts[0].pen_depth = rad - d;
    m.contacts[0].normal = t / d;
    m.contacts[0].contact_point = m.contacts[0].normal * a->GetRadius() + a->GetTransform()->GetPos();
    m.contact_count = 1;
  }

  m.contact_count = 1;
  return m; //true
}

//
Manifold CD_SphereAABB(const Collider* c1, const Collider* c2)
{
  Manifold m;
  m.contact_count = 0;
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

    else if (v > bmax)
    {
      float val = (v - bmax);
      out += val * val;
    }

    return out;
  };

  // Squared distance
  float sq = 0.0f;

  //Rotate the sphere about the box
  glm::vec3 rotated_a = (b->GetTransform()->GetRot() * (a->GetTransform()->GetPos() - b->GetTransform()->GetPos())) + b->GetTransform()->GetPos();

  sq += check(rotated_a.x, b->GetMin().x, b->GetMax().x);
  sq += check(rotated_a.y, b->GetMin().y, b->GetMax().y);
  sq += check(rotated_a.z, b->GetMin().z, b->GetMax().z);

  if (sq - (a->GetRadius() * a->GetRadius()) <= 0.0f)
  {
	  m.contact_count = 1;
	  return m; //true
  }

  return m; //false
}

IntersectionType PointPlane(glm::vec3 a, const PlaneCollider b, float epsilon)
{
  //PlaneCollider plane = b.Normalized();
  float dist = glm::dot(glm::vec3(a.x, a.y, a.z), glm::vec3(b.GetNormal().x, b.GetNormal().y, b.GetNormal().z)) / glm::length(b.GetNormal());

  if (dist > epsilon)
    return IntersectionType::Inside;

  if (dist <= epsilon && dist >= -epsilon)
    return IntersectionType::Coplanar;

  return IntersectionType::Outside;
}

Manifold CD_SpherePlane(const Collider* c1, const Collider* c2)
{
  Manifold m;
  m.contact_count = 0;
  SphereCollider* a = (SphereCollider*)(c1);
  PlaneCollider* b = (PlaneCollider*)(c2);

  IntersectionType t = PointPlane(a->GetTransform()->GetPos() - b->GetTransform()->GetPos(), *b, a->GetRadius());

  if (t == IntersectionType::Coplanar)
  {
	m.contact_count = 1;
	return m; //true
  }

  return m; //false
}

Manifold CD_AABBPlane(const Collider* c1, const Collider* c2)
{
  Manifold m;
  m.contact_count = 0;
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
  {
	  m.contact_count = 1;
	  return m; //true
  }

  return m; //false
}

Manifold CD_AABBAABB(const Collider* c1, const Collider* c2)
{
  Manifold m;
  m.contact_count = 0;
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
    return m; //false
  }

  m.contact_count = 1;
  return m; //true
}

Manifold CD_CylinderSphere(const Collider* c1, const Collider* c2)
{
  Manifold m;
  m.contact_count = 0;
  CylinderCollider* a = (CylinderCollider*)(c1);
  SphereCollider* b = (SphereCollider*)(c2);

  return m;
}

Manifold CD_CylinderAABB(const Collider* c1, const Collider* c2)
{
  Manifold m;
  m.contact_count = 0;
  CylinderCollider* a = (CylinderCollider*)(c1);
  AABBCollider* b = (AABBCollider*)(c2);
  return m;
}

Manifold CD_CylinderPlane(const Collider* c1, const Collider* c2)
{
  Manifold m;
  m.contact_count = 0;
  CylinderCollider* a = (CylinderCollider*)(c1);
  PlaneCollider* b = (PlaneCollider*)(c2);
  return m;
}

Manifold CD_CylinderCylinder(const Collider* c1, const Collider* c2)
{
  Manifold m;
  m.contact_count = 0;
  CylinderCollider* a = (CylinderCollider*)(c1);
  CylinderCollider* b = (CylinderCollider*)(c2);
  return m;

}

Manifold CD_PlanePlane(const Collider* c1, const Collider* c2)
{
	Manifold m;
	m.contact_count = 0;
	PlaneCollider* a = (PlaneCollider*)(c1);
	PlaneCollider* b = (PlaneCollider*)(c2);

	if (a->GetNormal() == b->GetNormal() && a->GetTransform()->GetPos() != b->GetTransform()->GetPos())
		return m;

	m.contact_count = 1;
	return m;
}
