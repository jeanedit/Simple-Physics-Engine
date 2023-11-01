#include "Star.h"

Star::Star(int numPoints, float outerRadius, float innerRadius) {
	GenerateStar(numPoints, outerRadius, innerRadius);
}


void Star::GenerateStar(int numPoints, float outerRadius, float innerRadius) {
	std::vector<float> starVertices;
	std::vector<unsigned int> indices;

	starVertices.reserve(static_cast<size_t>(numPoints) * 2 * 3); // 2 points per star point, 3 components (x, y, z) per point
	indices.reserve(static_cast<size_t>(numPoints) * 3); // 3 indices per triangle

	for (int i = 0; i < numPoints; i++) {
		float t = i * 2 * PI / numPoints;

		// Outer point
		float xOuter = outerRadius * cos(t);
		float yOuter = outerRadius * sin(t);
		starVertices.push_back(xOuter);
		starVertices.push_back(yOuter);
		starVertices.push_back(0.0f);

		// Inner point
		float xInner = innerRadius * cos(t + PI / numPoints);
		float yInner = innerRadius * sin(t + PI / numPoints);
		starVertices.push_back(xInner);
		starVertices.push_back(yInner);
		starVertices.push_back(0.0f);

		// Indices for triangles
		int startIndex = i * 2;
		indices.push_back(startIndex);
		indices.push_back(startIndex + 1);
		indices.push_back((startIndex + 2) % (numPoints * 2));
	}

	m_VertexCount = indices.size();
	m_VA.Bind();
	m_VB.CreateVertexBuffer(starVertices.data(), static_cast<uint32_t>(starVertices.size()) * sizeof(float));
	m_IB.CreateIndexBuffer(indices.data(), static_cast<uint32_t>(indices.size()) * sizeof(uint32_t));

	VertexBufferLayout vbl;
	vbl.Push<float>(3);
	m_VA.AddBuffer(m_VB, vbl);
	m_VA.Unbind();
}

void Star::Draw(const Shader& shader) const {
	shader.Use();

	m_VA.Bind();
	glDrawElements(GL_TRIANGLES, m_VertexCount, GL_UNSIGNED_INT, 0);
	m_VA.Unbind();
}