#pragma once

#include "Buffer.h"


class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
private:
	uint32_t m_RendererID;

};
