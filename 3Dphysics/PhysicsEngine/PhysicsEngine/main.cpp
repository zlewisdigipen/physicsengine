/*
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
*/
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
#include <time.h>

#undef main

/*
void OnExit()
{
  freopen("dumpleak/log.txt", "w", stdout);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
  _CrtDumpMemoryLeaks();
  fclose(stdout);
}*/

int main()
{
  //For memory leak checking V put that infront of news
  //atexit(OnExit); (_NORMAL_BLOCK, __FILE__, __LINE__) 

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

  std::vector<Entity*> entity_list;

  //entity_list.push_back(new Entity(&cube_mesh, Transform(glm::vec3(2.0f, 0.0f, 0.0f)), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), new AABBCollider(glm::vec3(c_radius, c_radius, c_radius), glm::vec3(0.0f, 0.0f, -1.0f))));
  //entity_list.push_back(new Entity(&cylinder_mesh, Transform(glm::vec3(-2.0f, 0.0f, 0.0f)), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), new CylinderCollider(glm::vec3(-2.0f, 0.0f, 0.0f), cy_height, s_radius)));
  entity_list.push_back(new Entity(&plane_mesh, Transform(glm::vec3(0.0f, -3.0f, 0.0f)), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), new PlaneCollider(glm::vec3(0.0f, 1.0f, 0.0f), -3.0f)));
  entity_list.push_back(new Entity(&sphere_mesh, Transform(glm::vec3(2.0f, 5.0f, -1.0f)), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), new SphereCollider(s_radius)));
  //entity_list.push_back(new Entity(&sphere_mesh, Transform(glm::vec3(-2.0f, 0.0f, -1.0f)), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), new SphereCollider(s_radius)));

  //For stress test
  /*
  for (int i = 0; i < 15; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      //entity_list.push_back(new Entity(&cube_mesh, Transform(glm::vec3(-2.0f * i, 0.0f, 2.0f*j)), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), new AABBCollider(glm::vec3(c_radius, c_radius, c_radius), glm::vec3(-2.0f * i, 0.0f, 2.0f*j))));
      entity_list.push_back(new Entity(&sphere_mesh, Transform(glm::vec3(-2.0f * i, 0.0f, 2.0f*j)), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), new SphereCollider(glm::vec3(-1.0f, 0.0f, -1.0f), s_radius)));
    }
  }*/
	/*
    entity_list[0].GetTransform().GetRot() = glm::angleAxis(-counter, glm::normalize(glm::vec3(0.5f, 1.0f, 0.0f)));
    entity_list[1].GetTransform().GetRot() = glm::angleAxis(counter, glm::normalize(glm::vec3(0.5f, 1.0f, 0.0f)));
    entity_list[2].GetTransform().GetRot() = glm::angleAxis(counter, glm::normalize(glm::vec3(0.0f, 1.0f, 1.0f)));
	*/

  shader.Bind();

  if (SDL_SetRelativeMouseMode(SDL_TRUE))
    std::cout << SDL_GetError() << std::endl;

  //Frames stuff
  uint32_t current_tick = 0, last_tick = 0;
  float  dt = 0.0f;

  entity_list[1]->GetCollider()->GetRigibody().GetStatic() = false;
  entity_list[1]->GetCollider()->GetRigibody().GetDirection() = glm::vec3(0.0f, -1.0f, 0.0f);
  entity_list[1]->GetCollider()->GetRigibody().GetSpeed() = 0.05f;

  while (!display.Closed())
  {
    //Get dt
    current_tick = SDL_GetTicks();
    dt = (float)(current_tick - last_tick) / 1000.f;
    last_tick = current_tick;
    std::cout << "FPS: " << 1.0f / (dt) << std::endl;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Clear frame
    display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

    Physics_Update(entity_list);
    Graphics_Update(entity_list, camera, shader);

    //Updating the display
    display.SwapBuffer();


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
          
          /*
        case SDLK_l:
          entity_list[0]->GetCollider()->GetRigibody().GetDirection() += glm::vec3(0.1f, 0.0f, 0.0f);
          entity_list[0]->GetCollider()->GetRigibody().GetSpeed() += 1;
          break;
        case SDLK_j:
          entity_list[0]->GetCollider()->GetRigibody().GetDirection() += glm::vec3(-0.1f, 0.0f, 0.0f);
          entity_list[0]->GetCollider()->GetRigibody().GetSpeed() += 1;
          break;
          */

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

  //delete all the data
  for (unsigned i = 0; i < entity_list.size(); i++)
    delete entity_list[i];

  return 0;
}
