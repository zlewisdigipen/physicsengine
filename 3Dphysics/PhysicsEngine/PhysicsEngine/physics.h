#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

#include "entity.h"
#include <vector>
//#include "GJK.h"
//#include "EPA.h"
#include "SAT.h"
#include "sphere_collider.h"
#include "aabb_collider.h"
#include "plane_collider.h"
#include "cylinder_collider.h"

typedef struct
{
  unsigned e1;
  unsigned e2;
  //Penatration pen;
  glm::vec3 normal;

}Manifold;

void Physics_Update(std::vector<Entity*>& entity_list, bool gravity);

#endif // !PHYSICS_H

