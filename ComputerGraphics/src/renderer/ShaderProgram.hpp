#pragma once

class ShaderProgram
{
public:
	ShaderProgram(const char* vsFile, const char* fsFile);
	~ShaderProgram();
	void Activate() const;
	inline unsigned int GetRendererID() const;
private:
	unsigned int m_ProgramID;
};
