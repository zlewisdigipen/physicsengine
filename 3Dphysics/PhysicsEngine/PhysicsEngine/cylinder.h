#pragma once
#ifndef CYLINDER_H
#define CYLINDER_H

#include "mesh.h"
#include <vector>

class Cylinder
{
public:

  Cylinder(float height, float radius, int slices)
  {
    //Make bottom circle
    vertices.push_back(glm::vec3(0, height, 0));
    for (int i = 0; i < slices; i++)
    {
      float angle = (2.0f * glm::pi<float>() / slices) * i;
      vertices.push_back(glm::vec3(radius*cos(angle), height, radius*sin(angle)));
    }

    //Make top circle
    vertices.push_back(glm::vec3(0, -height, 0));
    for (int i = 0; i < slices; i++)
    {
      float angle = (2.0f * glm::pi<float>() / slices) * i;
      vertices.push_back(glm::vec3(radius*cos(angle), -height, radius*sin(angle)));
    }

    //Make triangle indicies
    for (int i = 0; i < slices; i++)
    {
      if (i + 2 > slices)
      {
        indices.push_back(0); indices.push_back(1); indices.push_back(i + 1);
        indices.push_back(i + slices + 2); indices.push_back(2 + slices); indices.push_back(slices + 1);
        indices.push_back(i + 1); indices.push_back(1); indices.push_back(2 + slices);
        indices.push_back(i + 1); indices.push_back(2 + slices); indices.push_back(i + slices + 2);
      }
      else
      {
        indices.push_back(i + slices + 2); indices.push_back(i + slices + 3); indices.push_back(1 + slices);
        indices.push_back(i + 1); indices.push_back(i + 2); indices.push_back(i + slices + 3);
        indices.push_back(i + 1); indices.push_back(i + slices + 3); indices.push_back(i + slices + 2);
        indices.push_back(0); indices.push_back(i + 2); indices.push_back(i + 1);
      }
    }
  }

  std::vector<Vertex> GetVertices() { return vertices; }
  std::vector<unsigned int> GetIndices() { return indices; }

private:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
};

#endif // !CYLINDER_H

