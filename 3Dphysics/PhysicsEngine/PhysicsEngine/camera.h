#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		perspective = glm::perspective(fov, aspect, zNear, zFar);
		position = pos;
		forward = glm::vec3(0, 0, 1.0f);
		up = glm::vec3(0, 1.0f, 0);
		pitch = 0.0f;
		yaw = 0.0f;
		camera_rot = glm::quat();
	}


	inline glm::mat4 GetViewProjection() const
	{
    glm::mat4 temp = glm::lookAt(position, position + forward, up);
    return perspective * temp;
	}

  void CameraUpdate()
  {
    glm::quat y_quat = glm::angleAxis(yaw, glm::vec3(1.0f, 0, 0));
    glm::quat p_quat = glm::angleAxis(pitch, glm::vec3(0, 1.0f, 0));
    camera_rot = p_quat * y_quat;

    forward = camera_rot * glm::vec4(0, 0, -1.0f, 0);
    up = camera_rot * glm::vec4(0, -1.0f, 0, 0);
  }

	glm::vec3& GetForward() { return forward; }
	glm::vec3& GetUp() { return up; }
	glm::vec3& GetPos() { return position; }
  float& GetPitch() { return pitch; }
  float& GetYaw() { return yaw; }
  glm::mat4 GetPerspective() {  return perspective; }
  glm::mat4 GetView() { return glm::lookAt(position, position + forward, up); }

private:
  glm::quat camera_rot;
  float pitch;
  float yaw;
	glm::mat4 perspective;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
};

#endif // !CAMERA_H

