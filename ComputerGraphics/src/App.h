#pragma once

#include "renderer/ShaderProgram.hpp"

class App
{
public:
	App();
	~App();
	void Update(double deltaTime);
private:
	ShaderProgram*	m_ShaderProgram;
	unsigned int	m_VAO, 
					m_VBO, 
					m_EBO;
};
