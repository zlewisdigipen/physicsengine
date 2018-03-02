#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "entity.h"
#include "camera.h"
#include "shader.h"
#include <vector>

//void Graphics_Init();
void Graphics_Update(std::vector<Entity>& entity_list, Camera& camera, Shader& shader);

#endif // !GRAPHICS_H