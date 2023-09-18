#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

void Camera::Update()
{
	m_Direction.x = cosf(glm::radians(yaw)) * cosf(glm::radians(pitch));
	m_Direction.y = sinf(glm::radians(pitch));
	m_Direction.z = sinf(glm::radians(yaw)) * cosf(glm::radians(pitch));
	m_Direction = glm::normalize(m_Direction);

	m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, near, far);
	m_ViewMatrix = glm::lookAt(position, position + m_Direction, { 0.0f, 1.0f, 0.0f });
}
