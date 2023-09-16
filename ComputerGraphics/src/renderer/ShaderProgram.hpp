#pragma once

#include <glm/mat4x4.hpp>

#include <string>

class ShaderProgram
{
public:
	ShaderProgram(const char* vsFile, const char* fsFile);
	~ShaderProgram();
	void Activate() const;
	inline unsigned int GetRendererID() const;

	void SetUniformMat4(const std::string& varName, const glm::mat4& matrix) const;
private:
	unsigned int m_ProgramID;
};

inline unsigned int ShaderProgram::GetRendererID() const
{
	return m_ProgramID;
}
