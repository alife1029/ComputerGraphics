#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

void Camera::Update()
{
	glm::vec3 direction;
	direction.x = cosf(glm::radians(yaw)) * cosf(glm::radians(pitch));
	direction.y = sinf(glm::radians(pitch));
	direction.z = sinf(glm::radians(yaw)) * cosf(glm::radians(pitch));
	direction = glm::normalize(direction);

	m_ProjectionMatrix = glm::perspective(glm::radians(fov), 1024.0f / 680.0f, 0.1f, 100.0f);
	m_ViewMatrix = glm::lookAt(position, position + direction, { 0.0f, 1.0f, 0.0f });
}
