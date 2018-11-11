/*
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
*/
#include <iostream>
#include <glm/gtc/constants.hpp>
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
#include <imgui/ImGuizmo.h>
#include <time.h>

#undef main

void EditTransform(const float *view, float *proj, Entity* se, ImGuizmo::OPERATION mOp, ImGuizmo::MODE mMo, int width, int height)
{
  glm::fmat4 matrix = se->GetTransform().GetModel();
  bool t = false;
  bool r = false;
  bool s = false;

  //Make Gizmos
  float matrixTranslation[3], matrixRotation[3], matrixScale[3];
  ImGuizmo::DecomposeMatrixToComponents(&matrix[0][0], matrixTranslation, matrixRotation, matrixScale);

  if (ImGui::InputFloat3("Tr", matrixTranslation, 3))
    t = true;
  if (ImGui::InputFloat3("Rt", matrixRotation, 3))
    r = true;
  if (ImGui::InputFloat3("Sc", matrixScale, 3))
    s = true;

  if(t || r || s)
    ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, &matrix[0][0]);

  //To start manipulating the entity
  ImGuizmo::SetRect(0.0f, 0.0f, (float)width, (float)height);
  ImGuizmo::Manipulate(view, proj, mOp, mMo, &matrix[0][0]);
  ImGuizmo::DecomposeMatrixToComponents(&matrix[0][0], matrixTranslation, matrixRotation, matrixScale);

  //Set transform
  if (t || mOp == ImGuizmo::TRANSLATE)
    se->GetTransform().SetPos(glm::vec3(matrixTranslation[0], matrixTranslation[1], matrixTranslation[2]));

  if (r || mOp == ImGuizmo::ROTATE)
    se->GetTransform().SetRot(glm::quat(((glm::pi<float>() / 180.0f) * glm::vec3(matrixRotation[0], matrixRotation[1], matrixRotation[2]))));

  if (s || mOp == ImGuizmo::SCALE)
    se->GetTransform().SetScale(glm::vec3(matrixScale[0], matrixScale[1], matrixScale[2]));
}

void OnExit()
{
  freopen("dumpleak/log.txt", "w", stdout);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
  _CrtDumpMemoryLeaks();
  fclose(stdout);
}

int main()
{
  //For memory leak checking V put that infront of news
  //atexit(OnExit); (_NORMAL_BLOCK, __FILE__, __LINE__);

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
  Camera camera(glm::vec3(0, 5.0f, 10.0f), glm::radians(-60.0f), display.Aspect(), 0.01f, 1000.0f);
  Shader shader("./res/basicShader");
  Mesh sphere_mesh(&(s.GetVertices()[0]), s.GetVertices().size(), &(s.GetIndices()[0]), s.GetIndices().size());
  Mesh cube_mesh(&(c.GetVertices()[0]), c.GetVertices().size(), cube_ind, sizeof(cube_ind) / sizeof(cube_ind[0]));
  Mesh cylinder_mesh(&(cy.GetVertices()[0]), cy.GetVertices().size(), &(cy.GetIndices()[0]), cy.GetIndices().size());
  Mesh plane_mesh(&(p.GetVertices()[0]), p.GetVertices().size(), &(p.GetIndices()[0]), p.GetIndices().size());

  std::vector<Entity*> entity_list;
  std::vector<std::string> names;

  unsigned test_num = 0;

  //EXAMPLE ON HOW TO MAKE EACH ENTITY

  /*
  entity_list.push_back(new Entity(&cube_mesh, Transform(glm::vec3(-2.0f, 0.0f, 0.0f)), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), new AABBCollider(glm::vec3(c_radius, c_radius, c_radius))));
  entity_list.push_back(new Entity(&cylinder_mesh, Transform(glm::vec3(0.0f, 0.0f, 0.0f)), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), new CylinderCollider(cy_height, s_radius)));
  entity_list.push_back(new Entity(&plane_mesh, Transform(glm::vec3(0.0f, -3.0f, 0.0f)), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), new PlaneCollider(glm::vec3(0.0f, 1.0f, 0.0f), -3.0f)));
  entity_list.push_back(new Entity(&sphere_mesh, Transform(glm::vec3(2.0f, 0.0f, 0.0f)), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), new SphereCollider(s_radius)));
  //entity_list.push_back(new Entity(&sphere_mesh, Transform(glm::vec3(-2.0f, 0.0f, 0.0f)), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), new SphereCollider(s_radius)));
  */


  //FOR STRESS TEST PURPOSES

  /*
  for (int i = 0; i < 15; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      //entity_list.push_back(new Entity(&cube_mesh, Transform(glm::vec3(-2.0f * i, 0.0f, 2.0f*j)), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), new AABBCollider(glm::vec3(c_radius, c_radius, c_radius), glm::vec3(-2.0f * i, 0.0f, 2.0f*j))));
      entity_list.push_back(new Entity(&sphere_mesh, Transform(glm::vec3(-2.0f * i, 0.0f, 2.0f*j)), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), new SphereCollider(glm::vec3(-1.0f, 0.0f, -1.0f), s_radius)));
    }
  }*/

  //EXAMPLES ON ROTATION AND RIGIDBODIES

	/*
    entity_list[0].GetTransform().GetRot() = glm::angleAxis(-counter, glm::normalize(glm::vec3(0.5f, 1.0f, 0.0f)));
    entity_list[1].GetTransform().GetRot() = glm::angleAxis(counter, glm::normalize(glm::vec3(0.5f, 1.0f, 0.0f)));
    entity_list[2].GetTransform().GetRot() = glm::angleAxis(counter, glm::normalize(glm::vec3(0.0f, 1.0f, 1.0f)));
    entity_list[0]->GetTransform().GetRot() = glm::angleAxis(sinf(counter * 0.1f), glm::normalize(glm::vec3(0.5f, 0.0f, 0.5f)));

	entity_list[1]->GetCollider()->GetRigibody().GetStatic() = false;
	entity_list[1]->GetCollider()->GetRigibody().GetDirection() = glm::vec3(0.0f, -1.0f, 0.0f);
	entity_list[1]->GetCollider()->GetRigibody().GetSpeed() = 0.05f;
	*/
  
  //THIS IS DEMO CODE

  /*
  
	if (test_num == 1 || test_num == 2)
	{
		for (unsigned i = 0; i < entity_list.size(); i++)
		{
			if (entity_list[i]->GetCollider()->colliding)
				entity_list[i]->GetColor() = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
			else
				entity_list[i]->GetColor() = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		}
	}

	if (test_num == 2)
	{
		entity_list[0]->GetTransform().GetRot() = glm::angleAxis(current_tick * 0.001f, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)));
	}


  case SDLK_l:
  if(test_num == 1 || test_num == 2)
  entity_list[0]->GetTransform().GetPos() += glm::vec3(0.1f, 0.0f, 0.0f);
  break;
  case SDLK_j:
  if(test_num == 1 || test_num == 2)
  entity_list[0]->GetTransform().GetPos() -= glm::vec3(0.1f, 0.0f, 0.0f);
  break;

  //DEMO CODE FOR DEMO
  case SDLK_1:
  for (unsigned i = 0; i < entity_list.size(); i++)
  delete entity_list[i];
  entity_list.clear();

  entity_list.push_back(new Entity(&sphere_mesh, Transform(glm::vec3(2.0f, 0.0f, 0.0f)), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), new SphereCollider(s_radius)));
  entity_list.push_back(new Entity(&sphere_mesh, Transform(glm::vec3(-2.0f, 0.0f, 0.0f)), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), new SphereCollider(s_radius)));

  test_num = 1;
  break;

  case SDLK_2:
  for (unsigned i = 0; i < entity_list.size(); i++)
  delete entity_list[i];
  entity_list.clear();

  entity_list.push_back(new Entity(&cube_mesh, Transform(glm::vec3(-2.0f, 0.0f, 0.0f)), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), new AABBCollider(glm::vec3(c_radius, c_radius, c_radius))));
  entity_list.push_back(new Entity(&sphere_mesh, Transform(glm::vec3(0.0f, 0.0f, 0.0f)), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), new SphereCollider(s_radius)));

  test_num = 2;
  break;

  case SDLK_3:
  for (unsigned i = 0; i < entity_list.size(); i++)
  delete entity_list[i];
  entity_list.clear();


  entity_list.push_back(new Entity(&sphere_mesh, Transform(glm::vec3(0.0f, 4.0f, 0.0f)), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), new SphereCollider(s_radius)));
  entity_list.push_back(new Entity(&plane_mesh, Transform(glm::vec3(0.0f, 0.0f, 0.0f)), glm::vec4(0.0f, 0.0f, 0.5f, 1.0f), new PlaneCollider(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f)));
  entity_list.push_back(new Entity(&plane_mesh, Transform(glm::vec3(4.0f, 0.0f, 0.0f), glm::quat(0.5f, 0.0f, 0.0f, 0.8660254f)), glm::vec4(0.0f, 0.5f, 0.0f, 1.0f), new PlaneCollider(glm::vec3(-0.866025f, -0.5f, 0.0f), 0.0f)));
  entity_list.push_back(new Entity(&plane_mesh, Transform(glm::vec3(-4.0f, 0.0f, 0.0f), glm::quat(-0.5f, 0.0f, 0.0f, 0.8660254f)), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f), new PlaneCollider(glm::vec3(0.866025f, -0.5f, 0.0f), 0.0f)));


  entity_list[0]->GetCollider()->GetRigibody().GetStatic() = false;
  entity_list[0]->GetCollider()->GetRigibody().GetDirection() = glm::vec3(-0.5f, -1.0f, 0.0f);
  entity_list[0]->GetCollider()->GetRigibody().GetSpeed() = 0.05f;


  test_num = 3;
  break;
  */

  shader.Bind();

  //Debug stuff
  uint32_t current_tick = 0, last_tick = 0;     //This is for checking how fast a full loop goes
  float  dt = 0.0f;                             //Fps
  bool move_cam = false;                        //This if for checking if camera can rotate
  bool pause_physics = false;                   //So when editing things don't mess up
  std::vector<float> dt_holder;                 //For fps tracker
  ImGuizmo::OPERATION mOp(ImGuizmo::TRANSLATE); //To pass in for gizmos to see which opperation to use
  ImGuizmo::MODE mMo(ImGuizmo::LOCAL);          //Which space are we editing the entities
  bool selected = false;                        //Check if there is a selected object in list box to spawn gizmos
  int s_entity = 0;                             //Index to which entity being used

  //std::vector<std::vector<

  //Set Vsync
  SDL_GL_SetSwapInterval(1);

  while (!display.Closed())
  {
    //Get dt
    current_tick = SDL_GetTicks();
    dt = 1000.0f / (float)(current_tick - last_tick);
    last_tick = current_tick;

    //Check for input
    SDL_Event e;
    
    while (SDL_PollEvent(&e))
    {
      ImGui_ImplSDL2_ProcessEvent(&e);
      
      if (!ImGui::GetIO().WantCaptureKeyboard)
      {
        if (e.type == SDL_QUIT)
          display.SetClosed(true);
        if (e.type == SDL_KEYDOWN)
        {
          switch (e.key.keysym.sym)
          {
          case SDLK_w:
            camera.GetPos() += camera.GetForward() * 0.07f;
            break;
          case SDLK_s:
            camera.GetPos() += -camera.GetForward() * 0.07f;
            break;
          case SDLK_a:
            camera.GetPos() += glm::cross(camera.GetForward(), camera.GetUp()) * 0.07f;
            break;
          case SDLK_d:
            camera.GetPos() += -glm::cross(camera.GetForward(), camera.GetUp()) * 0.07f;
            break;

            //For gizmos
          case SDLK_r:
            mOp = ImGuizmo::ROTATE;
            break;
          case SDLK_t:
            mOp = ImGuizmo::TRANSLATE;
            break;
          case SDLK_y:
            mOp = ImGuizmo::SCALE;
            break;

          case SDLK_l:
            mMo = ImGuizmo::LOCAL;
            break;
          case SDLK_k:
            mMo = ImGuizmo::WORLD;
            break;

          case SDLK_DELETE:
            if (!names.empty())
            {
              names.erase(names.begin() + s_entity);
              selected = false;
              delete entity_list[s_entity];
              entity_list.erase(entity_list.begin() + s_entity);
            }
            break;

          case SDLK_LCTRL:
            //HIDE CURSOR
            SDL_SetRelativeMouseMode(SDL_TRUE);
            move_cam = true;
            break;

          case SDLK_ESCAPE:
            display.SetClosed(true);
            break;
          default:
            break;
          }
        }
        if (e.type == SDL_KEYUP)
        {
          switch (e.key.keysym.sym)
          {
          case SDLK_LCTRL:
            SDL_SetRelativeMouseMode(SDL_FALSE);
            move_cam = false;
            break;

          default:
            break;
          }
        }
        if (e.type == SDL_MOUSEMOTION && move_cam)
        {
          camera.GetPitch() += -e.motion.xrel * 0.01f;
          camera.GetYaw() += -e.motion.yrel * 0.01f;
        }
      }
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(display.GetWindow());
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();

    //Make imgui button for physics
    {
      dt_holder.push_back(dt);
      if (dt_holder.size() > 120)
        dt_holder.erase(dt_holder.begin());

      ImGui::Begin("FPS Window");

      //Imgui window logic
      if (ImGui::Button("Pause"))
        pause_physics = !pause_physics;

      std::string fps = "FPS: " + std::to_string((int)dt);
      ImGui::Text(fps.c_str());
      ImGui::PlotLines("", &dt_holder[0], dt_holder.size(), 0, nullptr, 0.0f, 80.0f, ImVec2(0, 40));

      ImGui::End();
    }

    //Make edit window
    if (pause_physics)
    {
      //ImGuizmo::Enable(true);
      ImGui::Begin("Debug Window");

      //Add object
      if (ImGui::CollapsingHeader("Spawn"))
      {
        //Adding cube
        if (ImGui::Button("Cube"))
        {
          entity_list.push_back(new Entity(&cube_mesh, Transform(), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), new AABBCollider(glm::vec3(c_radius, c_radius, c_radius))));
          names.push_back("Object " + std::to_string(names.size() + 1));
        }

        //Adding sphere
        if (ImGui::Button("Sphere"))
        {
          entity_list.push_back(new Entity(&sphere_mesh, Transform(), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), new SphereCollider(s_radius)));
          names.push_back("Object " + std::to_string(names.size() + 1));
        }

        //Adding cylinder
        if (ImGui::Button("Cylinder"))
        {
          entity_list.push_back(new Entity(&cylinder_mesh, Transform(), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), new CylinderCollider(cy_height, s_radius)));
          names.push_back("Object " + std::to_string(names.size() + 1));
        }

        //Adding plane
        if (ImGui::Button("Plane"))
        {
          entity_list.push_back(new Entity(&plane_mesh, Transform(), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), new PlaneCollider(glm::vec3(0.0f, 1.0f, 0.0f), -3.0f)));
          names.push_back("Object " + std::to_string(names.size() + 1));
        }
      }

      //Make list of entities to select from
      //Translation so imgui works for list box
      const char ** arr = new const char * [names.size()];

      for (unsigned i = 0; i < names.size(); i++)
        arr[i] = names[i].c_str();

      ImGui::Text("Entities:");
      if (ImGui::ListBox("", &s_entity, arr, names.size(), 5))
        selected = true;
      ImGui::End();

      //Make gizmos for selected entity
      if (selected)
      {
        ImGui::Begin("Edit Window");
        Entity* se = entity_list[s_entity];
        glm::fmat4 view = camera.GetView();
        glm::fmat4 projection = camera.GetPerspective();
        //Translation so input text works
        char n[20] = { 0 };
        for (unsigned i = 0; i < names[s_entity].length(); i++)
          n[i] = names[s_entity][i];

        //replace names
        ImGui::PushID(1);
        ImGui::Text("Name:");
        ImGui::SameLine();
        if (ImGui::InputText("", n, 20))
          names[s_entity] = n;
        ImGui::PopID();

        EditTransform(&view[0][0], &projection[0][0], se, mOp, mMo, display.GetWidth(), display.GetHeight());

        //Rigidbody stuff
        ImGui::PushID(2);
        ImGui::Text("Speed:");
        ImGui::SameLine();
        ImGui::InputFloat("", &se->GetCollider()->GetRigibody().GetSpeed(), 0.0f, 10.0f, 1);
        ImGui::PopID();

        ImGui::PushID(3);
        ImGui::Text("Static:");
        ImGui::SameLine();
        ImGui::Checkbox("", &(se->GetCollider()->GetRigibody().GetStatic()));
        ImGui::PopID();
        
        ImGui::End();
        //delete[] n;
      }

      delete[] arr;
    }

    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Clear frame
    display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

    if(!pause_physics)
      Physics_Update(entity_list);

    Graphics_Update(entity_list, camera, shader);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //Updating the display
    display.SwapBuffer();

  }

  //delete all the data
  for (unsigned i = 0; i < entity_list.size(); i++)
    delete entity_list[i];
  entity_list.clear();

  return 0;
}
