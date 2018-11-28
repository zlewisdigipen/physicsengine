#include "BarycentricCoordinates.h"

bool BarycentricCoordinates(const glm::vec3& point, const glm::vec3& a, const glm::vec3& b,
  float& u, float& v, float expansionEpsilon)
{
  /******Student:Assignment1******/
  //Warn("Assignment1: Required function un-implemented");
  glm::vec3 temp = a - b;
  float dot = glm::dot(temp, temp);

  if (dot == 0)
  {
    u = 0;
    v = 0;
    return false;
  }

  u = glm::dot((point - b), temp) / dot;
  v = 1 - u;

  if (u < -expansionEpsilon || v < -expansionEpsilon)
    return false;

  return true;
}

bool BarycentricCoordinates(const glm::vec3& point, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c,
  float& u, float& v, float& w, float expansionEpsilon)
{
  /******Student:Assignment1******/
  //Warn("Assignment1: Required function un-implemented");
  glm::vec3 v0 = point - c;
  glm::vec3 v1 = a - c;
  glm::vec3 v2 = b - c;

  float dot1 = glm::dot(v0, v1);
  float dot2 = glm::dot(v1, v1);
  float dot3 = glm::dot(v2, v1);
  float dot4 = glm::dot(v0, v2);
  float dot5 = glm::dot(v2, v2);

  float den = (dot2 * dot5 - dot3 * dot3);

  if (den == 0)
  {
    u = 0;
    v = 0;
    w = 0;
    return false;
  }

  //Cramers rule
  u = (dot1 * dot5 - dot3 * dot4) / den;
  v = (dot2 * dot4 - dot1 * dot3) / den;

  w = 1 - u - v;

  if (u < -expansionEpsilon || v < -expansionEpsilon || w < -expansionEpsilon)
    return false;

  return true;
}
