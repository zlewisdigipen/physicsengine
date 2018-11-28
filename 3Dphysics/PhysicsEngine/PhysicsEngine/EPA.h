#pragma once
#ifndef EPA_H
#define EPA_H

#include <vector>
#include <glm\glm.hpp>

//This is to just keep clean and keep things on track
typedef struct Triangle
{
  glm::vec3 points[3];
  glm::vec3 crs;

  Triangle(const glm::vec3& _a, const glm::vec3& _b, const glm::vec3& _c)
  {
    points[0] = _a;
    points[1] = _b;
    points[2] = _c;
    crs = glm::cross(_b - _a, _c - _a);
  }
}Triangle;

typedef struct Edge
{
  glm::vec3 points[2];

  Edge(const glm::vec3& _a, const glm::vec3& _b)
  {
    points[0] = _a;
    points[1] = _b;
  }
}Edge;

glm::vec3 EPA(const std::vector<glm::vec3>& shape_a, const std::vector<glm::vec3>& shape_b, std::vector<glm::vec3>& poly);


#endif // EPA_H

