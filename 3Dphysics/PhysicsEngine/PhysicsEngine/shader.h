#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include "transform.h"
#include "camera.h"

class Shader
{
public:
	Shader(const std::string& file_name);
	~Shader();

	void Bind();
	void Update(const Transform& transform, const Camera& camera, glm::vec4 color);

private:
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		TRANSFORM_U,
    COLOR_U,

		NUM_UNIFORMS
	};

	GLuint program;
	GLuint shaders[NUM_SHADERS];
	GLuint uniforms[NUM_UNIFORMS];
};

#endif // !SHADER_H
