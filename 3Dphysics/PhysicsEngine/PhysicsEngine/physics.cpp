#include "physics.h"
#include <iostream>

DetectionType detection_lookup[ColliderType::NumberOfColliderType][ColliderType::NumberOfColliderType] = {{ CD_SphereSphere,   CD_SphereAABB,   CD_CylinderSphere,   CD_SpherePlane },
                                                                                                          { CD_SphereAABB,     CD_AABBAABB,     CD_CylinderAABB,     CD_AABBPlane },
                                                                                                          { CD_CylinderSphere, CD_CylinderAABB, CD_CylinderCylinder, CD_CylinderPlane},
                                                                                                          { CD_SpherePlane,    CD_AABBPlane,    CD_CylinderPlane,    CD_PlanePlane }};

ResponseType response_lookup[ColliderType::NumberOfColliderType][ColliderType::NumberOfColliderType] = { { CR_SphereSphere,   CR_SphereAABB,   CR_CylinderSphere,   CR_SpherePlane },
                                                                                                         { CR_SphereAABB,     CR_AABBAABB,     CR_CylinderAABB,     CR_AABBPlane },
                                                                                                         { CR_CylinderSphere, CR_CylinderAABB, CR_CylinderCylinder, CR_CylinderPlane },
                                                                                                         { CR_SpherePlane,    CR_AABBPlane,    CR_CylinderPlane,    CR_PlanePlane} };

void Physics_Update(std::vector<Entity*>& entity_list)
{
  //Update colliders here
  for (unsigned i = 0; i < entity_list.size(); i++)
  {
    
    if (!entity_list[i]->GetCollider()->GetRigibody().GetStatic())
    {
      entity_list[i]->GetTransform().GetPos() += glm::normalize(entity_list[i]->GetCollider()->GetRigibody().GetDirection()) *
                                                                entity_list[i]->GetCollider()->GetRigibody().GetSpeed();
      //entity_list[i]->GetCollider()->GetRigibody().GetDirection() += glm::vec3(0.0f, -0.001f, 0.0f);
    }

   entity_list[i]->GetCollider()->UpdateCollider(&(entity_list[i])->GetTransform());
  }

  std::vector<Manifold> manifolds;

  //Collision Detection and update colliders
  for (unsigned i = 0; i < entity_list.size(); i++)
  {
    for (unsigned j = i + 1; j < entity_list.size(); j++)
    {
      const Collider* c1 = (*entity_list[i]).GetCollider();
      const Collider* c2 = (*entity_list[j]).GetCollider();

      if (c1->GetType() < c2->GetType())
      {
        Manifold m = detection_lookup[c1->GetType()][c2->GetType()](c1, c2);
        if (m.contact_count > 0)
        {
          //std::cout << m.contacts[0].pen_depth << std::endl;
          manifolds.push_back(m);
          response_lookup[c1->GetType()][c2->GetType()](c1, c2);

		  (*entity_list[i]).GetCollider()->colliding = true;
		  (*entity_list[j]).GetCollider()->colliding = true;
        }
		else
		{
			(*entity_list[i]).GetCollider()->colliding = false;
			(*entity_list[j]).GetCollider()->colliding = false;
		}
      }
      else
      {
        Manifold m = detection_lookup[c1->GetType()][c2->GetType()](c2, c1);
        if (m.contact_count > 0)
        {
          //std::cout << m.contacts[0].pen_depth << std::endl;
          manifolds.push_back(m);
          response_lookup[c1->GetType()][c2->GetType()](c2, c1);

		  (*entity_list[i]).GetCollider()->colliding = true;
		  (*entity_list[j]).GetCollider()->colliding = true;
		}
		else
		{
			(*entity_list[i]).GetCollider()->colliding = false;
			(*entity_list[j]).GetCollider()->colliding = false;
		}
      }
    }
  }

  //Last loop for manifold resolutions

  manifolds.clear();
}

