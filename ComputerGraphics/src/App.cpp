#include "App.h"

#include <glad/glad.h>
#include <glm/vec3.hpp>

#include <iostream>

App::App()
{
	m_VAO = m_VBO = m_EBO = 0;

	m_ShaderProgram = new ShaderProgram("assets/shaders/shader.vs.glsl", "assets/shaders/shader.fs.glsl");

	// Model data
	const float vertices[] = {
		// Position				// Color
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,
	};
	const unsigned short indices[] = {0, 1, 2};

	// Create vertex buffer
	glCreateBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create vertex array object
	glCreateVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)0);		// Position attrib
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)12);	// Color attrib
	glEnableVertexArrayAttrib(m_VAO, 0);
	glEnableVertexArrayAttrib(m_VAO, 1);
	
	// Create element array object
	glCreateBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

App::~App()
{
	delete m_ShaderProgram;

	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void App::Update(double deltaTime)
{
	glClearColor(0.5f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_ShaderProgram->Activate();

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (const void*)0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::cout << int(1 / deltaTime) << " FPS" << std::endl;
}
