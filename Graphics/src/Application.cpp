#include "Application.h"


// Initialize GLFW and OpenGL
bool OpenGLApp::Initialize() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
	if (!m_Window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_Window);

	// Initialize Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize Glad" << std::endl;
		return false;
	}

	// Set GLFW callback functions
	//glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetCursorPosCallback(m_Window, MouseCallback);
	glfwSetScrollCallback(m_Window, ScrollCallback);
	glfwSetFramebufferSizeCallback(m_Window, ResizeCallback);
	glfwSetKeyCallback(m_Window, KeyCallback);

	return true;
}

// Main rendering loop
void OpenGLApp::Run() {
	if (!m_Window) {
		std::cerr << "Window not initialized." << std::endl;
		return;
	}

	while (!glfwWindowShouldClose(m_Window)) {
		ProcessInput();
		Render();
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}



// Clean up resources
void OpenGLApp::Terminate() {
	if (m_Window) {
		glfwDestroyWindow(m_Window);
	}
	glfwTerminate();
}


void OpenGLApp::MouseCallback(GLFWwindow* window, double xPos, double yPos) {
	OpenGLApp* app = static_cast<OpenGLApp*>(glfwGetWindowUserPointer(window));
	if (app) {
		app->HandleMouseCallback(xPos, yPos);
	}
}

void OpenGLApp::HandleMouseCallback(double xPos, double yPos) {
	if (m_FirstMouse) {
		m_LastMouseX = xPos;
		m_LastMouseY = yPos;
		m_FirstMouse = false;
	}

	double xOffset = xPos - m_LastMouseX;
	double yOffset = m_LastMouseY - yPos; // Reversed for inverted Y-axis
	m_LastMouseX = xPos;
	m_LastMouseY = yPos;

	ProcessMouseInput(xOffset, yOffset);
}


// Static member function for GLFW scroll callback
void OpenGLApp::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	OpenGLApp* app = static_cast<OpenGLApp*>(glfwGetWindowUserPointer(window));
	if (app) {
		app->HandleScrollCallback(yOffset);
	}
}

void OpenGLApp::HandleScrollCallback(double yOffset) {
	// Update the scroll offset
	m_ScrollOffset = yOffset;
	// Call the user-defined scroll input processing function
	ProcessScrollInput(yOffset);
}

void OpenGLApp::ResizeCallback(GLFWwindow* window, int newWidth, int newHeight) {
	OpenGLApp* app = static_cast<OpenGLApp*>(glfwGetWindowUserPointer(window));
	if (app) {
		app->HandleResize(newWidth, newHeight);
	}
}

void OpenGLApp::HandleResize(int newWidth, int newHeight) {
	// Update the viewport dimensions
	glViewport(0, 0, newWidth, newHeight);

	// You can also update your projection matrix or other variables here
	// Example: projection = glm::perspective(glm::radians(fov), (float)newWidth / newHeight, near, far);

	// Call any user-defined resize handling code
	OnResize(newWidth, newHeight);
}

void OpenGLApp::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	OpenGLApp* app = static_cast<OpenGLApp*>(glfwGetWindowUserPointer(window));
	if (app) {
		app->HandleKeyCallback(key, scancode, action, mods);
	}
}


void OpenGLApp::HandleKeyCallback(int key, int scancode, int action, int mods) {
	ProcessKeyboardInput(key, action);
}