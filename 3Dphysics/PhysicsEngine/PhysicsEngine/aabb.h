#pragma once
#ifndef AABB_H
#define AABB_H

#include "mesh.h"
#include <vector>

class Cube
{
public:

  Cube(float radius)
  {
    vertices.push_back(glm::vec3(-radius, radius, radius));
    vertices.push_back(glm::vec3(-radius, -radius, radius));
    vertices.push_back(glm::vec3(radius, radius, radius));
    vertices.push_back(glm::vec3(radius, -radius, radius));

    vertices.push_back(glm::vec3(-radius, radius, -radius));
    vertices.push_back(glm::vec3(-radius, -radius, -radius));
    vertices.push_back(glm::vec3(radius, radius, -radius));
    vertices.push_back(glm::vec3(radius, -radius, -radius));
  }

  std::vector<Vertex> GetVertices() { return vertices; }

private:
  std::vector<Vertex> vertices;
};
/*
unsigned int cube_ind[] = { 0, 1, 3, 2,
0, 4, 5, 1,
4, 6, 7, 5,
6, 2, 3, 7,
3, 1, 5, 7,
6, 4, 0, 2 };


Vertex square_verts[] = { Vertex(glm::vec3(-0.5, 0.5, 0.5)),
Vertex(glm::vec3(-0.5, -0.5, 0.5)),
Vertex(glm::vec3(0.5, 0.5, 0.5)),
Vertex(glm::vec3(0.5, -0.5, 0.5)),
Vertex(glm::vec3(-0.5, 0.5, -0.5)),
Vertex(glm::vec3(-0.5, -0.5, -0.5)),
Vertex(glm::vec3(0.5, 0.5, -0.5)),
Vertex(glm::vec3(0.5, -0.5, -0.5)) };
*/
unsigned int cube_ind[] = { 0, 1, 2,
                             2, 1, 3,
                             4, 6, 7,
                             4, 7, 5,
                             6, 2, 3,
                             6, 3, 7,
                             0, 4, 5,
                             0, 5, 1,
                             6, 4, 0,
                             6, 0, 2,
                             3, 1, 5,
                             7, 3, 5 };

#endif // !SQUARE_H
