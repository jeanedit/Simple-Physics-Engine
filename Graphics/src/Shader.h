#pragma once
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
 // include glad to get all the required OpenGL headers


class Shader {
public:
	// constructor reads and builds the shader
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	// use/activate the shader
	void Use() const;
	// utility uniform functions
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetVec2(const std::string& name, const glm::vec2& value) const;
	void SetVec2(const std::string& name, float x, float y) const;
	void SetVec3(const std::string& name, const glm::vec3& value) const;
	void SetVec3(const std::string& name, float x, float y, float z) const;
	void SetVec4(const std::string& name, const glm::vec4& value) const;
	void SetVec4(const std::string& name, float x, float y, float z, float w) const;
	void SetMat2(const std::string& name, const glm::mat2& mat) const;
	void SetMat3(const std::string& name, const glm::mat3& mat) const;
	void SetMat4(const std::string& name, const glm::mat4& mat) const;


	inline unsigned int GetID() const {
		return m_ID;
	}

private:
	unsigned int m_ID;
	int m_Success;
	char m_InfoLog[512];

	unsigned int CompileShader(GLenum type, const std::string& shader_source);

	unsigned int CreateShader(unsigned int vertexShader, unsigned int fragmentShader);
};


