#pragma once
#include <cstdint>
#include <vector>
#include <random>
#include <array>

#include "particle.h"
#include "Application.h"
#include "VertexArray.h"
#include "Star.h"

static std::random_device rd;
static std::mt19937 rand_gen(rd());


class Firework : public cyclone::Particle {
public:
	Firework() = default;
	Firework(uint32_t type, float age)
		:m_Type(type),
		m_Age(age) {}

	bool Update(float duration) {
		Integrate(duration);
		m_Age -= duration;
		return (m_Age < 0) || (m_Position.GetY() < 0);
	}

	friend class FireworksDemo;
private:
	uint32_t m_Type = 0;
	float m_Age = 0.0f;

};

class FireworkRule {
public:
	FireworkRule() :
		m_PayloadCount(0) {}

	void Init(uint32_t payload_count);

	void SetParameters(uint32_t type, float min_age, float max_age,
		const cyclone::Vector3& min_velocity, const cyclone::Vector3& max_velocity,
		float damping);

	Firework Create(const Firework* parent = nullptr) const;
	friend class FireworksDemo;
private:
	uint32_t m_Type = 0;
	float m_MinAge = 0.0f;
	float m_MaxAge = 0.0f;
	cyclone::Vector3 m_MinVelocity;
	cyclone::Vector3 m_MaxVelocity;
	float m_Damping = 0.0f;

	struct Payload {
		uint32_t type;
		uint32_t count;

		void Set(uint32_t _type, uint32_t _count) {
			type = _type;
			count = _count;
		}
	};

	uint32_t m_PayloadCount;
	std::vector<Payload> m_Payloads;

};


class FireworksDemo final : public OpenGLApp {
public:
	/** Creates a new demo object. */
	FireworksDemo(int width, int height, std::string&& title);

	void Update() override;

	void Render() override;

	void Run() override;

	void ProcessKeyboardInput(int key, int action) override;

private:

	static const uint32_t MAX_FIREWORKS = 1024;
	static const uint32_t RULE_COUNT = 9;
	static glm::mat4 projection;

	/* variables */
	std::array<Firework, MAX_FIREWORKS> m_Fireworks;
	std::array<FireworkRule, RULE_COUNT> m_FRules;
	uint32_t m_NextFirework = 0;
	std::shared_ptr<Camera> m_Camera;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<Star> m_Star;

	// ------------ /* functions */ ------------------------
	void InitializeData();
	void InitFireworkRules();
	/** Dispatches a firework from the origin. */
	void Create(uint32_t type, const Firework* parent = nullptr);

	/** Dispatches the given number of fireworks from the given parent. */
	void Create(uint32_t type, uint32_t number, const Firework* parent);
};