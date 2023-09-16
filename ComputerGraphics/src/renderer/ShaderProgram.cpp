#include "ShaderProgram.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "../utils/File.hpp"

void AttachShader(GLuint programID, const std::string& shaderFile, GLenum shaderType)
{
	const std::string shaderSrc = File::Read(shaderFile);
	const char* shaderSrcC = shaderSrc.c_str();
	
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSrcC, NULL);
	glCompileShader(shader);

	// Compile error handling
	int isCompiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	
	if (!isCompiled)
	{
		char log[1024];
		glGetShaderInfoLog(shader, 1024, NULL, log);

		std::cout	<< "Failed to compile shader!" << std::endl
					<< "\nGPU Log:" << std::endl << log;
	}
	else
	{
		glAttachShader(programID, shader);
	}

	glDeleteBuffers(1, &shader);
}

void LinkShaderProgram(GLuint program)
{
	glLinkProgram(program);

	// Does linking successful?
	int isLinked;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	
	if (!isLinked)
	{
		char log[1024];
		glGetProgramInfoLog(program, 1024, NULL, log);
		std::cout	<< "Failed to link shader program!" << std::endl
					<< "\nGPU Log:" << std::endl << log;
	}
}

ShaderProgram::ShaderProgram(const char* vsFile, const char* fsFile)
{
	m_ProgramID = glCreateProgram();
	AttachShader(m_ProgramID, vsFile, GL_VERTEX_SHADER);
	AttachShader(m_ProgramID, fsFile, GL_FRAGMENT_SHADER);
	LinkShaderProgram(m_ProgramID);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ProgramID);
}

void ShaderProgram::Activate() const
{
	glUseProgram(m_ProgramID);
}

void ShaderProgram::SetUniformMat4(const std::string& varName, const glm::mat4& matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(GetRendererID(), varName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}
