#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "camera.h"
#include "aabb.h"
#include "sphere.h"
#include "cylinder.h"
#include "plane.h"
#include "entity.h"
#include "graphics.h"
#include "physics.h"

#undef main

int main()
{
  //Sphere stuff
	float s_radius = 0.75f;
  Sphere s(.5f, s_radius, .0f);

  //Cube stuff
  float c_radius = 0.5f;
  Cube c(c_radius);

  //Cylinder stuff
  float cy_height = 0.65f;
  Cylinder cy(cy_height, 0.75f, 16);

  //Plane stuff
  Plane p(15.0f);

  //Graphics
  Display display(800, 600, "Physics Engine");
  Camera camera(glm::vec3(0, 5.0f, 6.0f), 80.0f, display.Aspect(), 0.01f, 1000.0f);
  Shader shader("./res/basicShader");
  Mesh sphere_mesh(&(s.GetVertices()[0]), s.GetVertices().size(), &(s.GetIndices()[0]), s.GetIndices().size());
  Mesh cube_mesh(&(c.GetVertices()[0]), c.GetVertices().size(), cube_ind, sizeof(cube_ind) / sizeof(cube_ind[0]));
  Mesh cylinder_mesh(&(cy.GetVertices()[0]), cy.GetVertices().size(), &(cy.GetIndices()[0]), cy.GetIndices().size());
  Mesh plane_mesh(&(p.GetVertices()[0]), p.GetVertices().size(), &(p.GetIndices()[0]), p.GetIndices().size());

  std::vector<Entity> entity_list;
  entity_list.push_back(Entity(&cube_mesh, Transform(glm::vec3(2.0f, 0.0f, 0.0f)), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), new AABBCollider(glm::vec3(c_radius, c_radius, c_radius), glm::vec3(0.0f, 0.0f, -1.0f))));
  //entity_list.push_back(Entity(&sphere_mesh, Transform(glm::vec3(-2.0f, 0.0f, 0.0f)), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), new SphereCollider(glm::vec3(-1.0f, 0.0f, -1.0f), s_radius)));
  entity_list.push_back(Entity(&sphere_mesh, Transform(glm::vec3(0.0f, 0.0f, -1.0f)), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), new SphereCollider(glm::vec3(1.0f, 0.0f, -1.0f), s_radius)));
  entity_list.push_back(Entity(&cylinder_mesh, Transform(glm::vec3(-2.0f, 0.0f, 0.0f)), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), new CylinderCollider(glm::vec3(-2.0f, 0.0f, 0.0f), cy_height, s_radius)));
  entity_list.push_back(Entity(&plane_mesh, Transform(glm::vec3(0.0f, -3.0f, 0.0f)), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), new PlaneCollider(glm::vec3(0.0f, 1.0f, 0.0f), -3.0f)));

  //For stress test
  
  /*for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      //entity_list.push_back(Entity(&cube_mesh, Transform(glm::vec3(-2.0f * i, 0.0f, 2.0f*j)), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), new AABBCollider(glm::vec3(c_radius, c_radius, c_radius), glm::vec3(-2.0f * i, 0.0f, 2.0f*j))));
      //entity_list.push_back(Entity(&sphere_mesh, Transform(glm::vec3(-2.0f * i, 0.0f, 2.0f*j)), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), new SphereCollider(glm::vec3(-1.0f, 0.0f, -1.0f), s_radius)));
    }
  }*/

  shader.Bind();

  if (SDL_SetRelativeMouseMode(SDL_TRUE))
    std::cout << SDL_GetError() << std::endl;

  int framecount = 0;
  

  while (!display.Closed())
  {
    //Clear frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

	/*
    entity_list[0].GetTransform().GetRot() = glm::angleAxis(-counter, glm::normalize(glm::vec3(0.5f, 1.0f, 0.0f)));
    entity_list[1].GetTransform().GetRot() = glm::angleAxis(counter, glm::normalize(glm::vec3(0.5f, 1.0f, 0.0f)));
    entity_list[2].GetTransform().GetRot() = glm::angleAxis(counter, glm::normalize(glm::vec3(0.0f, 1.0f, 1.0f)));
	*/

    Graphics_Update(entity_list, camera, shader);
    Physics_Update(entity_list);

    //Updating the display
    display.SwapBuffer();
    uint32_t ticks = SDL_GetTicks();
    framecount++;

    std::cout << "FPS: " << (float)framecount / ((float)ticks / 1000.0f) << std::endl;



    //Check for input
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
        display.SetClosed(true);
      if (e.type == SDL_KEYDOWN)
      {
        switch (e.key.keysym.sym)
        {
        case SDLK_w:
          camera.GetPos() += camera.GetForward() * 0.05f;
          break;
        case SDLK_s:
          camera.GetPos() += -camera.GetForward() * 0.05f;
          break;
        case SDLK_a:
          camera.GetPos() += glm::cross(camera.GetForward(), camera.GetUp()) * 0.05f;
          break;
        case SDLK_d:
          camera.GetPos() += -glm::cross(camera.GetForward(), camera.GetUp()) * 0.05f;
          break;
        case SDLK_ESCAPE:
          display.SetClosed(true);
          break;
        default:
          break;
        }
      }
      if (e.type == SDL_MOUSEMOTION)
      {
        camera.GetPitch() += -e.motion.xrel * 0.01f;
        camera.GetYaw() += -e.motion.yrel * 0.01f;
      }
    }
  }

  return 0;
}
