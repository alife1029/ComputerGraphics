#pragma once

#include "renderer/ShaderProgram.hpp"

class App
{
public:
	App();
	~App();
	void Update(double deltaTime);
private:
	ShaderProgram* m_ShaderProgram;
};
