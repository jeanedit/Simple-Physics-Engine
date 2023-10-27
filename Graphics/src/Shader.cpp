#include <glm/glm.hpp>

#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>




Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) 
	:m_ID(0), 
	m_Success(0) 
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}


	unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertexCode);
	unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

	m_ID = CreateShader(vertex, fragment);

}

unsigned int Shader::CompileShader(GLenum type, const std::string& shader_source) {
	unsigned int shader;
	shader = glCreateShader(type);
	const char* shader_ptr = shader_source.c_str();
	glShaderSource(shader, 1, &shader_ptr, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &m_Success);
	if (!m_Success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, m_InfoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << m_InfoLog << std::endl;
	};

	return shader;
}


unsigned int Shader::CreateShader(unsigned int vertexShader, unsigned int fragmentShader) {
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);

	glGetProgramiv(m_ID, GL_LINK_STATUS, &m_Success);
	if (!m_Success)
	{
		glGetProgramInfoLog(m_ID, 512, nullptr, m_InfoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << m_InfoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}



void Shader::Use() const {
	glUseProgram(m_ID);
}

void Shader::SetBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}
void Shader::SetInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}
void Shader::SetFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}
void Shader::SetVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}
void Shader::SetVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}
void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
