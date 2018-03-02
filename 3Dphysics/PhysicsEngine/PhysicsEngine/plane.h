#pragma once
#ifndef PLANE_H
#define PLANE_H

#include "mesh.h"
#include <vector>

class Plane
{

protected:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

public:

	Plane(float radius)
	{
		vertices.push_back(glm::vec3(radius, 0, radius));
		vertices.push_back(glm::vec3(-radius, 0, radius));
		vertices.push_back(glm::vec3(-radius, 0, -radius));
		vertices.push_back(glm::vec3(radius, 0, -radius));

		indices.push_back(0); indices.push_back(2); indices.push_back(1);
		indices.push_back(0); indices.push_back(3); indices.push_back(2);
	}

	std::vector<Vertex> GetVertices() { return vertices; }
	std::vector<unsigned int> GetIndices() { return indices; }
};

#endif // !PLANE_H

