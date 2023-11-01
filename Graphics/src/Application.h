#pragma once
#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <string>
#include <functional>
#include <iostream>

#include "Camera.h"
#include "Shader.h"

class OpenGLApp {
public:
	OpenGLApp(int width, int height, std::string&& title)
		: m_Width(width),
		m_Height(height),
		m_Title(std::move(title))
	{
	}

	// Initialize GLFW and OpenGL
	bool Initialize();

	virtual void Update() {}

	// Main rendering loop
	virtual void Run();

	// User-defined rendering function (override this in derived classes)
	virtual void Render() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	// Clean up resources
	void Terminate();

	~OpenGLApp() {
		Terminate();
	}

	inline const GLFWwindow* GetWindow() const {
		return m_Window;
	}

	static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
	static void ResizeCallback(GLFWwindow* window, int newWidth, int newHeight);
	static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void HandleResize(int newWidth, int newHeight);
	void HandleMouseCallback(double xPos, double yPos);
	void HandleScrollCallback(double yOffset);
	void HandleKeyCallback(int key, int scancode, int action, int mods);

	virtual void OnResize(int newWidth, int newHeight) {}
	virtual void ProcessMouseInput(double xOffset, double yOffset) {}
	virtual void ProcessScrollInput(double yOffset) {}
	virtual void ProcessKeyboardInput(int key, int action) {}

protected:
	GLFWwindow* m_Window = nullptr;

	// Window parameters
	int m_Width = 800;
	int m_Height = 600;

	// Member variables for mouse input
	double m_LastMouseX = 0.0;
	double m_LastMouseY = 0.0;
	bool m_FirstMouse = true;

	// Scroll offset
	double m_ScrollOffset = 0.0;
	// Window title
	std::string m_Title = "OpenGLApp";
};