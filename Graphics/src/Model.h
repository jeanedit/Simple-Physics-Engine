#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"
#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"

static const float PI = 3.14159265358979323846f;

class Model {
public:
	virtual void Draw(const Shader& shader) const = 0;
	inline const glm::mat4& GetModelMatrix() const {
		return m_ModelMatrix;
	}

	void ResetModelMatrix() {
		m_ModelMatrix = glm::mat4(1.0f);
	}

	void Rotate(float rotation_angle, const glm::vec3& axis);
	void Translate(const glm::vec3& vec);
	void Scale(const glm::vec3& vec);
protected:
	VertexArray m_VA;
	VertexBuffer m_VB;
	glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
};