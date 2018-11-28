#pragma once
#ifndef GJK_H
#define GJK_H
#include <vector>
#include <glm/glm.hpp>

struct CsoPoint
{
  glm::vec3 mPointA;
  glm::vec3 mPointB;
  glm::vec3 mCsoPoint;
};

glm::vec3 FarthestPoint(const std::vector<glm::vec3>& shape, const glm::vec3 &direction);
bool GJK_Intersection(const std::vector<glm::vec3>& shape_a, const std::vector<glm::vec3>& shape_b, glm::vec3& direction, std::vector<glm::vec3>& poly);

#endif