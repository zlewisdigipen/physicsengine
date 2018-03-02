#include "graphics.h"

void Graphics_Update(std::vector<Entity*>& entity_list, Camera& camera, Shader& shader)
{
  camera.CameraUpdate();
  for(auto e = entity_list.begin(); e != entity_list.end(); e++)
  {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    shader.Update((*e)->GetTransform(), camera, (*e)->GetColor());
    (*e)->GetMesh()->Draw();

	  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	  shader.Update((*e)->GetTransform(), camera, glm::vec4(0.0f,0.0f,0.0f,1.0f));
	  (*e)->GetMesh()->Draw();
  }
}
