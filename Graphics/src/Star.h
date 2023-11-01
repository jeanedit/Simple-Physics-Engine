#pragma once
#include "Model.h"
#include "VertexArray.h"

class Star : public Model {
public:
	Star(int numPoints, float outerRadius, float innerRadius);
	virtual void Draw(const Shader& shader) const override;
private:
	int m_NumPoints;
	float m_OuterRadius;
	float m_InnerRadius;
	IndexBuffer m_IB;
	uint32_t m_VertexCount;
	void GenerateStar(int numPoints, float outerRadius, float innerRadius);
};


