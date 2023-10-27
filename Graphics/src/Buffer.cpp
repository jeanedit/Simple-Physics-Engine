#include "Buffer.h"
#include <glad/glad.h>
#include <iostream>


//////////////////
/* Vertex Buffer */
//////////////////

VertexBuffer::VertexBuffer(const void* data, uint32_t size_bytes) {
	CreateVertexBuffer(data, size_bytes);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::SetData(const void* data, uint32_t size_bytes) {
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size_bytes, data);
}

void VertexBuffer::CreateVertexBuffer(const void* data, uint32_t size_bytes) {
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size_bytes, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::UnBind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int VertexBuffer::GetRendererID() const {
	return m_RendererID;
}

//////////////////
/* Index Buffer */
//////////////////


IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t size_bytes) {
	CreateIndexBuffer(data, size_bytes);
}



IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &m_RendererID);
}


void IndexBuffer::CreateIndexBuffer(const uint32_t* data, uint32_t size_bytes) {
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_bytes, data, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::UnBind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}