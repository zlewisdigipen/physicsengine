#pragma once

#ifndef SAT_H
#define SAT_H
#include <vector>
#include <glm/glm.hpp>

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
    if (glm::length(crs) != 0.0f)
      crs = glm::normalize(crs);
  }
}Triangle;

typedef struct Edge
{
  glm::vec3 points[2];
  glm::vec3 direction;

  Edge(const glm::vec3& _a, const glm::vec3& _b)
  {
    points[0] = _a;
    points[1] = _b;

    direction = _b - _a;
  }
}Edge;

typedef struct Interval
{
  float min, max;
}Interval;

typedef struct Query
{
  float seperation;
  bool using_face;
  int face_ind;
  int edge1_ind;
  int edge2_ind;
}Query;

std::vector<Edge> GetEdges(const std::vector<glm::vec3>& shape);
std::vector<Triangle> GetFaces(const std::vector<glm::vec3>& shape);
glm::vec3 FarthestPoint(const std::vector<glm::vec3>& shape, const glm::vec3& direction);
Query QueryFaceDirections(const std::vector<Triangle>& tri, const std::vector<glm::vec3>& shape);
Query QueryEdgeDirections(const std::vector<glm::vec3>& shape_a, const std::vector<glm::vec3>& shape_b);
bool OverLap(const std::vector<glm::vec3>& shape_a, const std::vector<glm::vec3>& shape_b, glm::vec3& normal);

#endif
