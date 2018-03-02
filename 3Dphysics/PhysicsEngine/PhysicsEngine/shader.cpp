#include "shader.h"
#include <fstream>
#include <iostream>

static void CheckShaderError(GLuint shader, GLuint flag, bool is_program, const std::string& error_mess);
static std::string LoadShader(const std::string& file_name);
static GLuint CreateShader(const std::string& text, GLenum shader_type);

Shader::Shader(const std::string& file_name)
{
	program = glCreateProgram();
	shaders[0] = CreateShader(LoadShader(file_name + ".vs"), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShader(file_name + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; ++i)
		glAttachShader(program, shaders[i]);

	glBindAttribLocation(program, 0, "position");

  //Ling and validate program
	glLinkProgram(program);
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Program failed to link: ");

	glValidateProgram(program);
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Program failed to validate: ");

  //Get the uniforms in .vs and .fs
	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
  uniforms[COLOR_U] = glGetUniformLocation(program, "color");
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; ++i)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	glDeleteProgram(program);
}

void Shader::Bind()
{
	glUseProgram(program);
}

void Shader::Update(const Transform& transform, const Camera& camera, glm::vec4 color)
{
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, &mvp[0][0]);
  glUniform4f(uniforms[COLOR_U], color.x, color.y, color.z, color.w);
}

static GLuint CreateShader(const std::string& text, GLenum shader_type)
{
	GLuint shader = glCreateShader(shader_type);

	if (shader == 0)
		std::cerr << "Error: Shader creation failed" << std::endl;

	const GLchar* shader_string[1];
	GLint shader_string_len[1];

	shader_string[0] = text.c_str();
	shader_string_len[0] = text.length();

	glShaderSource(shader, 1, shader_string, shader_string_len);
	glCompileShader(shader);


	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}

static std::string LoadShader(const std::string& file_name)
{
	std::ifstream file;
	file.open(file_name.c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
		std::cerr << "Unable to load shader: " << file_name << std::endl;

	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool is_program, const std::string& error_mess)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (is_program)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (is_program)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << error_mess << ": " << error << "'" << std::endl;
	}
}
