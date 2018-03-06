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
  }

  glm::vec3& GetDirection() { return dir; }
  float& GetSpeed() { return speed; }
  bool& GetStatic() { return is_static; }

private:
  glm::vec3 dir;
  float speed;
  bool is_static;
};

#endif // !RIGIDBODY_H

