#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <string>



class Texture {
public:
	Texture(const std::string& path, GLint internalFormat, GLenum format);
	~Texture();
	void Bind(unsigned int slot = 0) const;

	void Unbind();

	inline int GetWidth() const {
		return m_Width;
	}
	inline int GetHeight() const {
		return m_Height;
	}
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;


};

