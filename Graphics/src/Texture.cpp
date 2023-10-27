#include "Texture.h"

#include <stb_image.h>
#include <iostream>


Texture::Texture(const std::string& path,GLint internalFormat, GLenum format)
	:m_RendererID(0),
	m_FilePath(path),
	m_LocalBuffer(nullptr),
	m_Width(0),
	m_Height(0),
	m_BPP(0)
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	// load and generate the texture
	stbi_set_flip_vertically_on_load(true);

	m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 0);
	if (m_LocalBuffer) {
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot /*= 0*/) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

