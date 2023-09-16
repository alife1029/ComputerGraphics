#pragma once

#include "renderer/ShaderProgram.hpp"
#include "components/Camera.hpp"

class App
{
public:
	App();
	~App();
	void Update(float deltaTime);
	void Render();
private:
	ShaderProgram*	m_ShaderProgram;
	unsigned int	m_VAO, 
					m_VBO, 
					m_EBO;
	Camera			m_Camera;
};
