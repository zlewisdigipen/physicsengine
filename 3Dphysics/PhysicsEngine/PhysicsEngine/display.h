#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string>

class Display
{
public:
	Display(int width, int height, const std::string& title);
	~Display();

	void SwapBuffer();
	void Clear(float r, float g, float b, float a);
	bool Closed();
	void SetClosed(bool closed);

	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
	float Aspect() { return (float)m_width / m_height; }

private:

	SDL_Window* wndptr;
	SDL_GLContext gl_context;

	int m_width;
	int m_height;

	bool is_closed;
};

#endif // ! DISPLAY_H
