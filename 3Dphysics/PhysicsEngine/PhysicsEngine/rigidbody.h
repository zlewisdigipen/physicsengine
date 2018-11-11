#pragma once
#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/glm.hpp>

class Rigibody
{
public:
  Rigibody()
  {
    dir = glm::vec3();
    speed = 0.0f;
    is_static = true;
    friction = 1.0f;
  }

  glm::vec3& GetDirection() { return dir; }
  float& GetSpeed() { return speed; }
  bool& GetStatic() { return is_static; }
  float& GetFriction() { return friction; }

private:
  glm::vec3 dir;
  float friction;
  float speed;
  bool is_static;
};

#endif // !RIGIDBODY_H

