#include "physics.h"
#include <iostream>

void Physics_Update(std::vector<Entity*>& entity_list, bool gravity
)
{
  //Update colliders here
  for (unsigned i = 0; i < entity_list.size(); i++)
  {
    //Gravity
    if (gravity && !(entity_list[i]->GetCollider()->GetRigibody().GetStatic()))
    {
      glm::vec3 norm;

      //Solve for 0 vector
      if (glm::length(entity_list[i]->GetCollider()->GetRigibody().GetDirection()) == 0.0f)
        norm = entity_list[i]->GetCollider()->GetRigibody().GetDirection();
      else
        norm = glm::normalize(entity_list[i]->GetCollider()->GetRigibody().GetDirection());

      entity_list[i]->GetTransform().GetPos() +=  norm * entity_list[i]->GetCollider()->GetRigibody().GetSpeed();
      entity_list[i]->GetCollider()->GetRigibody().GetDirection() += glm::vec3(0.0f, -0.001f, 0.0f);
    }

   entity_list[i]->GetCollider()->UpdateCollider(&(entity_list[i])->GetTransform());
  }

  std::vector<Manifold> manifolds;

  //Collision Detection and update colliders
  /*
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
  }*/

  //GJK Collision Detection
  //n^2 check << change it
  for (unsigned i = 0; i < entity_list.size(); i++)
  {
    for (unsigned j = i + 1; j < entity_list.size(); j++)
    {
      //if they are both static don't do gjk
      if (entity_list[i]->GetCollider()->GetRigibody().GetStatic() && entity_list[j]->GetCollider()->GetRigibody().GetStatic())
        continue;

      glm::vec3 dir = entity_list[i]->GetTransform().GetPos() - entity_list[j]->GetTransform().GetPos();
      std::vector<glm::vec3> poly;
      glm::vec3 normal;

      //GJK_Intersection(entity_list[i]->GetTransform().GetPoints(), entity_list[j]->GetTransform().GetPoints(), dir, poly)

      //SAT here
      if (OverLap(entity_list[i]->GetTransform().GetPoints(), entity_list[j]->GetTransform().GetPoints(), normal))
      {

        Manifold m;
        //Do EPA here
        //m.pen = EPA(entity_list[i]->GetTransform().GetPoints(), entity_list[i]->GetTransform().GetPoints(), poly);

        //Add Manifolds which hold epa information and more
        m.normal = normal;
        m.e1 = i;
        m.e2 = j;

        manifolds.push_back(m);
      }
      else
      {
        entity_list[i]->GetColor() = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
        entity_list[j]->GetColor() = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
      }
    }
  }

  //Last loop for manifold resolutions
  
  //This if to check if colliding
  for (unsigned i = 0; i < manifolds.size(); i++)
  {
    Entity* e1 = entity_list[manifolds[i].e1];
    Entity* e2 = entity_list[manifolds[i].e2];

    if (e1->GetCollider()->GetRigibody().GetStatic())
      e2->GetTransform().GetPos() -= manifolds[i].normal/10.0f;
    else if (e2->GetCollider()->GetRigibody().GetStatic())
      e1->GetTransform().GetPos() -= manifolds[i].normal/10.0f;
    else
    {

      e2->GetTransform().GetPos() += manifolds[i].normal/40.0f;
      e1->GetTransform().GetPos() -= manifolds[i].normal/40.0f;

    }

    e1->GetColor() = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    e2->GetColor() = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
  }

  manifolds.clear();
}

