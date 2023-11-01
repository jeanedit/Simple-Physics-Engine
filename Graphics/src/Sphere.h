#pragma once

#include "Model.h"


class Sphere : public Model {
public:
	Sphere(float radius, int sectors, int stacks);
	void Draw(const Shader& shader) const override;
	//void Update() override;

private:
	IndexBuffer m_IB;
	int vertexCount;

	void GenerateSphere(float radius, int sectors, int stacks);
};
