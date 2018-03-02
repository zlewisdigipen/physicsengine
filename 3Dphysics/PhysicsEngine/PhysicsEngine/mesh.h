#pragma once
#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex
{
public:
  Vertex()
  {
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
  }

	Vertex(const glm::vec3 & pos)
	{
		this->pos = pos;
	}

	glm::vec3* GetPos() { return &pos; }
  void SetPos(const glm::vec3 vec) { pos = vec; }

private:
	glm::vec3 pos;
};

class Mesh
{
public:
  Mesh() { draw_count = 0; }
	Mesh(Vertex* verts, unsigned int num_verts, unsigned int* indices, unsigned int num_indices);
	~Mesh();

	void Draw();

private:

	enum
	{
		POSITION_VB,
		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint vertex_objs;
	GLuint vertex_buff[NUM_BUFFERS];
	unsigned int draw_count;
};

#endif // !MESH_H
