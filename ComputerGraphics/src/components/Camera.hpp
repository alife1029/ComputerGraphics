#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	inline glm::mat4 GetViewMatrix() const;
	inline glm::mat4 GetProjectionMatrix() const;
	inline glm::mat4 GetCombinedMatrix() const;

	void Update();

public:
	float		fov					= 45.0f;
	float		yaw				= 0.0f,
				pitch				= 0.0f,
				roll				= 0.0f;
	glm::vec3	position			{ 0.0f };

private:
	glm::mat4	m_ProjectionMatrix	{ 1.0f };
	glm::mat4	m_ViewMatrix		{ 1.0f };
};

inline glm::mat4 Camera::GetViewMatrix() const
{
	return m_ViewMatrix;
}

inline glm::mat4 Camera::GetProjectionMatrix() const
{
	return m_ProjectionMatrix;
}

inline glm::mat4 Camera::GetCombinedMatrix() const
{
	return m_ProjectionMatrix * m_ViewMatrix;
}
