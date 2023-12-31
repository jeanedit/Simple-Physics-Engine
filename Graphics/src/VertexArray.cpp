#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const {
	glBindVertexArray(m_RendererID);
}
void VertexArray::Unbind() const {
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	vb.Bind();
	const auto& elements = layout.GetElements();
	uint32_t offset = 0;
	for (uint32_t i = 0; i < elements.size(); ++i) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*) offset);
		offset += element.count * VertexBufferElement::GetTypeSize(element.type);
	}
}