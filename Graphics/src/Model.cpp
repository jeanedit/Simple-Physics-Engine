#include "Model.h"

void Model::Rotate(float rotation_angle, const glm::vec3& axis) {
	m_ModelMatrix = glm::rotate(m_ModelMatrix, rotation_angle, axis);
}
void Model::Translate(const glm::vec3& vec) {
	m_ModelMatrix = glm::translate(m_ModelMatrix, vec);
}

void Model::Scale(const glm::vec3& vec) {
	m_ModelMatrix = glm::scale(m_ModelMatrix, vec);
}