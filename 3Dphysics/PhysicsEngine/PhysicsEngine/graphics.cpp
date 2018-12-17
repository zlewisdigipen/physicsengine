#include "graphics.h"

void rotate_vector_by_quaternion(const glm::vec3& v, const glm::quat& q, glm::vec3& vprime)
{
  // Extract the vector part of the quaternion
  glm::vec3 u(q.x, q.y, q.z);

  // Extract the scalar part of the quaternion
  float s = q.w;

  // Do the math
  vprime = 2.0f * glm::dot(u, v) * u
    + (s*s - glm::dot(u, u)) * v
    + 2.0f * s * glm::cross(u, v);
}

void Graphics_Update(std::vector<Entity*>& entity_list, Camera& camera, Shader& shader)
{
  camera.CameraUpdate();
  for(auto e = entity_list.begin(); e != entity_list.end(); e++)
  {

    //Object
	  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    shader.Update((*e)->GetTransform(), camera, (*e)->GetColor());
    (*e)->GetMesh()->Draw();

    //Move to physics if problems later on, this updates point shapes
    if ((*e)->GetTransform().GetPoints().empty())
      (*e)->GetTransform().GetPoints().resize((*e)->GetMesh()->GetShape().size());

    for (unsigned i = 0; i < (*e)->GetMesh()->GetShape().size(); i++)
    {
      //to mat3
      glm::vec3 temp;
      rotate_vector_by_quaternion((*e)->GetMesh()->GetShape()[i], (*e)->GetTransform().GetRot(), temp);
      (*e)->GetTransform().GetPoints()[i] = (*e)->GetTransform().GetPos() + temp;
    }

    //Wire Frame
	  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	  shader.Update((*e)->GetTransform(), camera, glm::vec4(0.0f,0.0f,0.0f,1.0f));
	  (*e)->GetMesh()->Draw();
  }
}
