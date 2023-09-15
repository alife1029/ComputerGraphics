#include "App.h"

#include <iostream>

App::App()
{
	m_ShaderProgram = new ShaderProgram("assets/shaders/shader.vs.glsl", "assets/shaders/shader.fs.glsl");
}

App::~App()
{
	delete m_ShaderProgram;
}

void App::Update(double deltaTime)
{
	m_ShaderProgram->Activate();
}
