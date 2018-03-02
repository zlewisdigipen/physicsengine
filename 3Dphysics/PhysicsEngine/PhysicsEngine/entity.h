#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "transform.h"
#include "mesh.h"
#include "collider.h"

class Entity
{
public:

	Entity(Mesh *m, Transform t, glm::vec4 color, Collider* collider)
  {
    m_color = color;
    m_mesh = m;
    m_transform = t;
	  m_collider = collider;
  }

  Transform& GetTransform() { return m_transform; }
  Mesh* GetMesh() { return m_mesh; }
  glm::vec4& GetColor() { return m_color; }
  Collider* GetCollider() { return m_collider; }

private:
  glm::vec4 m_color;
  Transform m_transform;
  Mesh* m_mesh;
  Collider* m_collider;
};

#endif // !ENTITY_H
