#pragma once
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Application.h"
#include "Sphere.h"
#include "Timing.h"
#include "particle.h"



class BallisticDemo final :public OpenGLApp {
public:
	BallisticDemo(int width, int height, std::string&& title)
		:OpenGLApp(width, height, std::move(title)),
		m_CurrentShotType(ShotType::UNUSED)
	{
	}

	void Update() override;

	void Render() override;


	void InitializeData();

	void Run() override;

	inline const GLFWwindow* GetWindow() const {
		return m_Window;
	}

	void ProcessMouseInput(double xOffset, double yOffset) override {}

	void ProcessKeyboardInput(int key, int action) override;

private:

	/* variables */
	static glm::vec3 lightPos;
	static glm::mat4 projection;
	std::shared_ptr<Camera> m_Camera;
	float m_RotationAngle = 0.0f;
	//std::unique_ptr<Sphere> m_Sphere;
	std::shared_ptr<Sphere> m_Sphere;
	std::unordered_map<std::string, std::shared_ptr<Shader>> m_StrToShader;

	/* auxilary */
	enum class ShotType {
		UNUSED,
		PISTOL,
		ARTILLERY,
		FIREBALL,
		LASER
	};

	struct AmmoRound {
		cyclone::Particle particle;
		ShotType shot_type = ShotType::UNUSED;
		uint64_t start_time;
		std::shared_ptr<Sphere> sphere;
		void Render(const Shader& shader);
	};
	

	static const uint32_t ammo_rounds = 16;
	std::array<AmmoRound,ammo_rounds> m_Ammo;
	ShotType m_CurrentShotType;

	/* functions */
	void Fire();
	void RenderStartSphere();
	void RenderLines(const VertexArray& vao, size_t ibo_size);
};
