
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

	// constructor with vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
		: m_Position(position), 
		m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
		m_WorldUp(up),
		m_Yaw(yaw),
		m_Pitch(pitch),
		m_MovementSpeed(SPEED),
		m_MouseSensitivity(SENSITIVITY),
		m_Zoom(ZOOM)
{
	UpdateCameraVectors();
}

	// constructor with scalar values
Camera::Camera(CameraPositionVector camera_pos, WorldUpVector world_up, float yaw, float pitch)
	: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_MovementSpeed(SPEED),
	m_MouseSensitivity(SENSITIVITY),
	m_Zoom(ZOOM)
{
	m_Position = glm::vec3(camera_pos.posX, camera_pos.posY, camera_pos.posZ);
	m_WorldUp = glm::vec3(world_up.upX, world_up.upY, world_up.upZ);
	m_Yaw = yaw;
	m_Pitch = pitch;
	UpdateCameraVectors();
}

	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix() const {
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

	// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime) {
	float velocity = m_MovementSpeed * deltaTime;
	if (direction == CameraMovement::FORWARD) {
		m_Position += m_Front * velocity;
	}

	if (direction == CameraMovement::BACKWARD) {
		m_Position -= m_Front * velocity;
	}

	if (direction == CameraMovement::LEFT) {
		m_Position -= m_Right * velocity;
	}

	if (direction == CameraMovement::RIGHT) {
		m_Position += m_Right * velocity;
	}
	
}

	// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (m_Pitch > 89.0f) {
			m_Pitch = 89.0f;
		}

		if (m_Pitch < -89.0f) {
			m_Pitch = -89.0f;
		}
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
	}

	// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset) {
	m_Zoom -= (float)yoffset;
	if (m_Zoom < 1.0f) {
		m_Zoom = 1.0f;
	}

	if (m_Zoom > 45.0f) {
		m_Zoom = 45.0f;
	}
}

void Camera::UpdateCameraVectors() {
	// calculate the new Front vector
	//glm::vec3 front;
	m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front.y = sin(glm::radians(m_Pitch));
	m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(m_Front);
	// also re-calculate the Right and Up vector
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}


