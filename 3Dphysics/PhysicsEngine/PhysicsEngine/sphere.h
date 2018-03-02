#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"
#include <vector>

class Sphere
{
protected:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

public:

  Sphere(float x, float z, float n)
  {
    vertices.push_back(glm::vec3( -x,  n,  z));
    vertices.push_back(glm::vec3( x,  n,  z));
    vertices.push_back(glm::vec3( -x,  n,  -z));
    vertices.push_back(glm::vec3( x,  n,  -z));

    vertices.push_back(glm::vec3( n,  z,   x));
    vertices.push_back(glm::vec3( n,  z,   -x));
    vertices.push_back(glm::vec3( n,  -z,   x));
    vertices.push_back(glm::vec3( n,  -z,   -x));

    vertices.push_back(glm::vec3( z,   x,   n));
    vertices.push_back(glm::vec3( -z,  x,   n));
    vertices.push_back(glm::vec3( z,   -x,   n));
    vertices.push_back(glm::vec3( -z,  -x,   n));


    indices.push_back(1); indices.push_back(4); indices.push_back(0);
    indices.push_back(4); indices.push_back(9); indices.push_back(0);
    indices.push_back(4); indices.push_back(5); indices.push_back(9);
    indices.push_back(8); indices.push_back(5); indices.push_back(4);
    indices.push_back(1); indices.push_back(8); indices.push_back(4);
    indices.push_back(1); indices.push_back(10); indices.push_back(8);
    indices.push_back(10); indices.push_back(3); indices.push_back(8);
    indices.push_back(8); indices.push_back(3); indices.push_back(5);
    indices.push_back(3); indices.push_back(2); indices.push_back(5);
    indices.push_back(3); indices.push_back(7); indices.push_back(2);

    indices.push_back(3); indices.push_back(10); indices.push_back(7);
    indices.push_back(10); indices.push_back(6); indices.push_back(7);
    indices.push_back(6); indices.push_back(11); indices.push_back(7);
    indices.push_back(6);  indices.push_back(0); indices.push_back(11);
    indices.push_back(6); indices.push_back(1); indices.push_back(0);
    indices.push_back(10); indices.push_back(1); indices.push_back(6);
    indices.push_back(11); indices.push_back(0); indices.push_back(9);
    indices.push_back(2); indices.push_back(11); indices.push_back(9);
    indices.push_back(5); indices.push_back(2); indices.push_back(9);
    indices.push_back(11); indices.push_back(2); indices.push_back(7);
  }

  std::vector<Vertex> GetVertices() { return vertices; }
  std::vector<unsigned int> GetIndices() { return indices; }
};

#endif // !CIRCLE_H
