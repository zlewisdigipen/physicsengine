#include "display.h"
#include <iostream>
#include <GL/glew.h>

Display::Display(int width, int height, const std::string& title)
{
	std::cout << "Constructed Display" << std::endl;
	SDL_Init(SDL_INIT_EVERYTHING);

	//Setting SDL bits for color
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	//Sets how much data a pixel has
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	//Allocate space for 2 windows
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Create Window
	wndptr = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_width = width;
	m_height = height;

	//Create Context
	gl_context = SDL_GL_CreateContext(wndptr);

	GLenum status = glewInit();

	if (status != GLEW_OK)
		std::cerr << "Glew failed to initialize" << std::endl;

	is_closed = false;

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); 
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);


  //Initialize imgui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  ImGui_ImplSDL2_InitForOpenGL(wndptr, gl_context);
  ImGui_ImplOpenGL3_Init("#version 130");

  ImGui::StyleColorsDark();
}

Display::~Display()
{

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(wndptr);

	SDL_Quit();
	std::cout << "Destructed Display" << std::endl;
}

void Display::SwapBuffer()
{
	SDL_GL_SwapWindow(wndptr);
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool Display::Closed()
{
	return is_closed;
}

void Display::SetClosed(bool closed)
{
	is_closed = closed;
}
