#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

#include "collision_detection.h"
#include "collision_response.h"
#include "entity.h"
#include <vector>

typedef Manifold (*DetectionType)(const Collider*, const Collider*);
typedef void (*ResponseType)(const Collider*, const Collider*);

void Physics_Update(std::vector<Entity*>& entity_list);

#endif // !PHYSICS_H

