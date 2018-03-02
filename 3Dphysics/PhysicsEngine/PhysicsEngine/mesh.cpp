#include "mesh.h"
#include <vector>
#include <iostream>

Mesh::Mesh(Vertex* verts, unsigned int num_verts, unsigned int* indices, unsigned int num_indices)
{
	draw_count = num_indices;

	glGenVertexArrays(1, &vertex_objs);
	glBindVertexArray(vertex_objs);

	std::vector<glm::vec3> positions;

	positions.reserve(num_verts);

	for (unsigned int i = 0; i < num_verts; i++)
		positions.push_back(*verts[i].GetPos());

	glGenBuffers(NUM_BUFFERS, vertex_buff);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buff[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, num_verts * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_buff[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertex_objs);
}

void Mesh::Draw()
{
  if (draw_count == 0)
    std::cerr << "No Mesh to draw" << std::endl;

	glBindVertexArray(vertex_objs);

	glDrawElements(GL_TRIANGLES, draw_count, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, draw_count);

	glBindVertexArray(0);
}
