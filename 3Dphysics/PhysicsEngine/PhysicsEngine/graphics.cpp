#include "graphics.h"

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
      glm::vec3 temp = (*e)->GetMesh()->GetShape()[i];
      (*e)->GetTransform().GetPoints()[i] = (*e)->GetTransform().GetPos() + temp;
    }

    //Wire Frame
	  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	  shader.Update((*e)->GetTransform(), camera, glm::vec4(0.0f,0.0f,0.0f,1.0f));
	  (*e)->GetMesh()->Draw();
  }
}
