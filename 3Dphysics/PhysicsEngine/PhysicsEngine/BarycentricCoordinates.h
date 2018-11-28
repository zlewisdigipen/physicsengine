#pragma once
#ifndef BARYCENTRICCOORDINATES_H
#define BARYCENTRICCOORDINATES_H

#include <glm/glm.hpp>

bool BarycentricCoordinates(const glm::vec3& point, const glm::vec3& a, const glm::vec3& b,
  float& u, float& v, float expansionEpsilon = 0.0f);

bool BarycentricCoordinates(const glm::vec3& point, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c,
  float& u, float& v, float& w, float expansionEpsilon = 0.0f);
#endif