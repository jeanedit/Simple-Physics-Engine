
#pragma once
#include <vector>
#include <glad/glad.h>
#include <cassert>
#include <cstdint>


class VertexBuffer {
public:
	VertexBuffer(const void* data, uint32_t size_bytes);
	VertexBuffer() = default;
	~VertexBuffer();

	VertexBuffer(const VertexBuffer& other) = delete;
	VertexBuffer(VertexBuffer&& other) = delete;
	VertexBuffer operator= (const VertexBuffer& other) = delete;
	VertexBuffer operator= (VertexBuffer&& other) = delete;

	void SetData(const void* data, uint32_t size_bytes);

	void CreateVertexBuffer(const void* data, uint32_t size_bytes);

	void Bind() const;
	void UnBind() const;

	unsigned int GetRendererID() const;

private:
	unsigned int m_RendererID = 0;
};

class IndexBuffer {
public:
	IndexBuffer(const uint32_t* data, uint32_t size_bytes);
	IndexBuffer() = default;
	~IndexBuffer();

	IndexBuffer(const IndexBuffer& other) = delete;
	IndexBuffer(IndexBuffer&& other) = delete;
	IndexBuffer operator= (const IndexBuffer& other) = delete;
	IndexBuffer operator= (IndexBuffer&& other) = delete;

	void CreateIndexBuffer(const uint32_t* data, uint32_t size_bytes);

	void Bind() const;
	void UnBind() const;

private:
	unsigned int m_RendererID = 0;
	//unsigned int m_Size;
};


struct VertexBufferElement {
	uint32_t type;
	uint32_t count;
	bool normalized;
	static uint32_t GetTypeSize(uint32_t type) {
		switch (type) {
		case GL_FLOAT:
			return sizeof(GLfloat);
		case GL_UNSIGNED_INT:
			return sizeof(GLuint);
		case GL_UNSIGNED_BYTE:
			return sizeof(GLubyte);
		default:
			assert(false);
			return 0;
		}
	}
};

class VertexBufferLayout {
public:
	using ElementVector = std::vector<VertexBufferElement>;
	VertexBufferLayout()
		:m_Stride(0)
	{
	}

	template<typename T>
	void Push(uint32_t count);

	inline const std::vector<VertexBufferElement>& GetElements() const {
		return m_Elements;
	}

	inline uint32_t GetStride() const {
		return m_Stride;
	}

private:
	std::vector<VertexBufferElement> m_Elements;
	uint32_t m_Stride;
};

template<typename T>
void VertexBufferLayout::Push(uint32_t count) {
	static_assert(false);
}

template <>
inline void VertexBufferLayout::Push<float>(uint32_t count) {
	m_Elements.push_back({ GL_FLOAT,count, false });
	m_Stride += count * VertexBufferElement::GetTypeSize(GL_FLOAT);
}

template <>
inline void VertexBufferLayout::Push<uint32_t>(uint32_t count) {
	m_Elements.push_back({ GL_UNSIGNED_INT,count, false });
	m_Stride += count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT);
}

template <>
inline void VertexBufferLayout::Push<unsigned char>(uint32_t count) {
	m_Elements.push_back({ GL_UNSIGNED_BYTE,count, true });
	m_Stride += count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE);
}