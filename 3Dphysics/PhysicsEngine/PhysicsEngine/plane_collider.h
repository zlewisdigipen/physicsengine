#pragma once
#ifndef PLANE_COLLIDER_H
#define PLANE_COLLIDER_H

#include <glm/glm.hpp>
#include "collider.h"

class PlaneCollider : public Collider
{
public:
	PlaneCollider(const glm::vec3 n, const float d) : normal(n), distance(d) 
  {
    type = ColliderType::PlaneType; 

    rig = Rigibody();
  }

	PlaneCollider Normalized() const 
	{
		float mag = (float)normal.length();
		return PlaneCollider(normal / mag, distance / mag);
	}

	const glm::vec3 GetNormal() const { return normal; }
	const float GetDistance() const { return distance; }

  void UpdateCollider(Transform* t) 
  {
    tran = t;
    //transform to normal
    glm::quat test(tran->GetRot());
    glm::quat test2(glm::inverse(tran->GetRot()));

    normal = normal;
  }

private:

  glm::vec3 normal;
	const float distance;

};

#endif
