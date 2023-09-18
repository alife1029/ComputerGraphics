#pragma once

#include "renderer/ShaderProgram.hpp"
#include "renderer/Texture.hpp"
#include "components/Camera.hpp"
#include "utils/Window.hpp"

class App
{
public:
	App();
	~App();
	void Update(float deltaTime);
	void Render();
public:
	Window* window;
private:
	ShaderProgram*	m_ShaderProgram;
	Texture*		m_Texture;
	unsigned int	m_VAO, 
					m_VBO, 
					m_EBO;
	Camera			m_Camera;
};
