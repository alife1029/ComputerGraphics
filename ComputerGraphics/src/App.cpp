#include "App.hpp"

#include <glad/glad.h>
#include <glm/vec3.hpp>

#include <iostream>

#include "utils/Input.hpp"
 
App::App()
{
	m_VAO = m_VBO = m_EBO = 0;

	m_ShaderProgram = new ShaderProgram("assets/shaders/shader.vs.glsl", "assets/shaders/shader.fs.glsl");
	m_Texture = new Texture("assets/textures/brick/COLOR.png");

	// Model data
	const float vertices[] = {
		// Position					// Color					// Tex Coords

		// FRONT FACE
		-0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		// BOTTOM-LEFT
		 0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,		// BOTTOM-RIGHT
		 0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		// TOP-RIGHT
		-0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f,		// TOP-LEFT

		// RIGHT FACE
		 0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		// BOTTOM-LEFT
		 0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,		// BOTTOM-RIGHT
		 0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		// TOP-RIGHT
		 0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f,		// TOP-LEFT

		 // LEFT FACE
		-0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		// BOTTOM-LEFT
		-0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,		// BOTTOM-RIGHT
		-0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		// TOP-RIGHT
		-0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f,		// TOP-LEFT

		// TOP FACE
		-0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		// BOTTOM-LEFT
		 0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,		// BOTTOM-RIGHT
		 0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		// TOP-RIGHT
		-0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f,		// TOP-LEFT

		// BOTTOM FACE
		-0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		// BOTTOM-LEFT
		 0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,		// BOTTOM-RIGHT
		 0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		// TOP-RIGHT
		-0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f,		// TOP-LEFT

		// BACK FACE
		 0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		// BOTTOM-LEFT
		-0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,		// BOTTOM-RIGHT
		-0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		// TOP-RIGHT
		 0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f,		// TOP-LEFT
	};
	const unsigned short indices[] = { 
		0,  1,  2,  2,  3,  0,	// Front face
		4,  5,  6,  6,  7,  4,	// Right face
		8,  9,  10, 10, 11, 8,	// Left face
		12, 13, 14, 14, 15, 12,	// Top face
		16, 17, 18, 18, 19, 16,	// Bottom face
		20, 21, 22, 22, 23, 20,	// Back face
	};

	// Create vertex buffer
	glCreateBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create vertex array object
	glCreateVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (const void*)0);		// Position attrib
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (const void*)12);	// Color attrib
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (const void*)28);	// Texture Coords attrib
	glEnableVertexArrayAttrib(m_VAO, 0);
	glEnableVertexArrayAttrib(m_VAO, 1);
	glEnableVertexArrayAttrib(m_VAO, 2);
	
	// Create element array object
	glCreateBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_Camera.position = { 2.0f, 2.0f, 2.0f };
	m_Camera.yaw = -135.0f;
	m_Camera.pitch = -35.0f;
}

App::~App()
{
	delete m_ShaderProgram;

	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void App::Update(float deltaTime)
{
	// Rotate camera
	if (Input::IsMouseButtonPressed(MouseButton::ButtonRight))
	{
		const float cameraSensitivity = 8.0f;
		m_Camera.yaw += Input::GetCursorDeltaX() * cameraSensitivity * deltaTime;
		m_Camera.pitch -= Input::GetCursorDeltaY() * cameraSensitivity * deltaTime;
		if (m_Camera.pitch > 89.9f) m_Camera.pitch = 89.9f;
		else if (m_Camera.pitch < -89.9f) m_Camera.pitch = -89.9f;
	}

	// Move camera
	const float cameraSpeed = 5.0f;
	if (Input::IsKeyPressed(Key::KEY_W)) m_Camera.position += m_Camera.GetFrontVector() * deltaTime * cameraSpeed;
	if (Input::IsKeyPressed(Key::KEY_A)) m_Camera.position -= m_Camera.GetRightVector() * deltaTime * cameraSpeed;
	if (Input::IsKeyPressed(Key::KEY_S)) m_Camera.position -= m_Camera.GetFrontVector() * deltaTime * cameraSpeed;
	if (Input::IsKeyPressed(Key::KEY_D)) m_Camera.position += m_Camera.GetRightVector() * deltaTime * cameraSpeed;

	// Update camera
	if (window->GetHeight() != 0) m_Camera.aspectRatio = static_cast<float>(window->GetWidth()) / window->GetHeight();
	m_Camera.Update();
}

void App::Render()
{
	glClearColor(0.5f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_ShaderProgram->Activate();
	m_ShaderProgram->SetUniformMat4("u_ViewMatrix", m_Camera.GetViewMatrix());
	m_ShaderProgram->SetUniformMat4("u_ProjectionMatrix", m_Camera.GetProjectionMatrix());

	m_Texture->Activate();

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (const void*)0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
