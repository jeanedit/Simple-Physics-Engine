#pragma once
 

#include <glm/glm.hpp>


// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum class CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


struct CameraPositionVector {
	float posX;
	float posY;
	float posZ;
};


struct WorldUpVector {
	float upX;
	float upY;
	float upZ;
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:

	// constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	// constructor with scalar values
	Camera(CameraPositionVector camera_pos, WorldUpVector world_up, float yaw, float pitch);

	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix() const;

	// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(CameraMovement direction, float deltaTime);

	// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

	// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset);

	inline float GetZoom() const { return m_Zoom; };

private:
	// camera Attributes
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;
	// euler Angles
	float m_Yaw;
	float m_Pitch;
	// camera options
	float m_MovementSpeed;
	float m_MouseSensitivity;
	float m_Zoom;

	// calculates the front vector from the Camera's (updated) Euler Angles
	void UpdateCameraVectors();
};

