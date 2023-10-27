#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>


#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"

static const float PI = 3.14159265358979323846f;

class Model {
public:
	virtual void Draw(const Shader& shader) = 0;
	virtual void Rotate(float rotation_angle, const glm::vec3& axis) = 0;
	virtual void Translate(const glm::vec3& vec) = 0;
	virtual void Scale(const glm::vec3& axis) = 0;
	//virtual void Update() = 0;
};

class Sphere : public Model {
public:
	Sphere(float radius, int sectors, int stacks);
	void Draw(const Shader& shader) override;
	//void Update() override;
	inline const glm::mat4& GetModelMatrix() const {
		return m_ModelMatrix;
	}

	virtual void Rotate(float rotation_angle, const glm::vec3& axis) override;
	virtual void Translate(const glm::vec3& vec) override;
	virtual void Scale(const glm::vec3& axis) override;

	void ResetModelMatrix() {
		m_ModelMatrix = glm::mat4(1.0f);
	}

private:
	VertexArray m_VA;
	VertexBuffer m_VB;
	IndexBuffer m_IB;
	int vertexCount;

	glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

	void GenerateSphere(float radius, int sectors, int stacks);
};
