#include "Sphere.h"
#include <glm/gtc/matrix_transform.hpp>

Sphere::Sphere(float radius, int sectors, int stacks) {
	GenerateSphere(radius, sectors, stacks);
}

void Sphere::GenerateSphere(float radius, int sectors, int stacks) {
	std::vector<float> vertices;
	std::vector<uint32_t> indices;
	float sectorStep = 2 * PI / sectors;
	float stackStep = PI / stacks;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stacks; ++i) {
		stackAngle = PI / 2 - i * stackStep;

		for (int j = 0; j <= sectors; ++j) {
			sectorAngle = j * sectorStep;

			float x = radius * cos(stackAngle) * cos(sectorAngle);
			float y = radius * cos(stackAngle) * sin(sectorAngle);
			float z = radius * sin(stackAngle);

			// Vertex positions (x, y, z)
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// Texture coordinates (u, v)
			float u = static_cast<float>(j) / static_cast<float>(sectors);
			float v = static_cast<float>(i) / static_cast<float>(stacks);

			vertices.push_back(u);
			vertices.push_back(v);

			// Normal vectors (x, y, z)
			float nx = x / radius;
			float ny = y / radius;
			float nz = z / radius;

			vertices.push_back(nx);
			vertices.push_back(ny);
			vertices.push_back(nz);
		}
	}

	// Generate indices for rendering as triangles
	for (int i = 0; i < stacks; ++i) {
		for (int j = 0; j < sectors; ++j) {
			int first = i * (sectors + 1) + j;
			int second = first + sectors + 1;

			indices.push_back(first);
			indices.push_back(second);
			indices.push_back(first + 1);

			indices.push_back(second);
			indices.push_back(second + 1);
			indices.push_back(first + 1);
		}
	}

	vertexCount = static_cast<int>(indices.size());

	m_VA.Bind();
	m_VB.CreateVertexBuffer(vertices.data(), static_cast<uint32_t>(vertices.size()) * sizeof(float));
	m_IB.CreateIndexBuffer(indices.data(), static_cast<uint32_t>(indices.size()) * sizeof(uint32_t));

	VertexBufferLayout vbl;
	vbl.Push<float>(3);
	vbl.Push<float>(2);
	vbl.Push<float>(3);
	m_VA.AddBuffer(m_VB, vbl);
	m_VA.Unbind();
}

void Sphere::Draw(const Shader& shader) const {
	shader.Use();

	m_VA.Bind();
	glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
	m_VA.Unbind();
}
