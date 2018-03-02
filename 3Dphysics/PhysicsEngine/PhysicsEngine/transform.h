#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::quat& rot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), const glm::vec3& sca = glm::vec3(1.0f, 1.0f, 1.0f)) :
		position(pos),
		rotation(rot),
		scale(sca) {}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 pos_mat = glm::translate(position);
		glm::mat4 rot_mat = glm::mat4_cast(rotation);
		glm::mat4 scale_mat = glm::scale(scale);

		return pos_mat * rot_mat * scale_mat;
	}

	inline glm::vec3& GetPos() { return position; }
	inline glm::quat& GetRot() { return rotation; }
	inline glm::vec3& GetScale() { return scale; }

	inline void SetPos(glm::vec3& pos) { position = pos; }
	inline void SetRot(glm::quat& rot) { rotation = rot; }
	inline void SetScale(glm::vec3& sca) { scale = sca; }

private:

	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

};

#endif // !TRANSFORM_H

