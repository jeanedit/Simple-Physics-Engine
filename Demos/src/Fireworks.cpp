#include "Fireworks.h"
#include "Timing.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <filesystem>

glm::mat4 FireworksDemo::projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 1.0f, 600.0f);

void FireworkRule::Init(uint32_t payload_count) {
	m_PayloadCount= payload_count;
	m_Payloads.resize(payload_count);
}

void FireworkRule::SetParameters(uint32_t type, float minAge, float maxAge,
	const cyclone::Vector3& minVelocity, const cyclone::Vector3& maxVelocity,
	float damping) 
{
	m_Type = type;
	m_MinAge = minAge;
	m_MaxAge = maxAge;
	m_MinVelocity = minVelocity;
	m_MaxVelocity = maxVelocity;
	m_Damping = damping;
}


Firework FireworkRule::Create(const Firework* parent) const {
	std::uniform_real_distribution<float> age(m_MinAge, m_MaxAge);
	Firework firework(m_Type, age(rand_gen));

	cyclone::Vector3 vel;
	if (parent) {
		// The position and velocity are based on the parent.
		firework.SetPosition(parent->GetPosition());
		vel += parent->GetVelocity();
	}
	else {
		cyclone::Vector3 start;
		std::uniform_int_distribution<int> x_dist(-1, 1);
		int x = x_dist(rand_gen);
		start.SetX(2.0f * static_cast<float>(x));
		firework.SetPosition(start);
	}


	auto rand_vec = [](const cyclone::Vector3& min, const cyclone::Vector3& max) {
		std::uniform_real_distribution<float> vx_dist(min.GetX(), max.GetX());
		std::uniform_real_distribution<float> vy_dist(min.GetY(), max.GetY());
		std::uniform_real_distribution<float> vz_dist(min.GetZ(), max.GetZ());
		return cyclone::Vector3(vx_dist(rand_gen), vy_dist(rand_gen), vz_dist(rand_gen));
	};

	vel += rand_vec(m_MinVelocity, m_MaxVelocity);
	firework.SetVelocity(vel);

	// We use a mass of one in all cases (no point having fireworks
	// with different masses, since they are only under the influence
	// of gravity).
	firework.SetMass(1);

	firework.SetDamping(m_Damping);

	firework.SetAcceleration(cyclone::Vector3::GRAVITY);

	firework.ClearAccumulator();
	return firework;
}


// Method definitions
FireworksDemo::FireworksDemo(int width, int height, std::string&& title)
	:OpenGLApp(width, height, std::move(title)),
	m_NextFirework(0)
{
	InitFireworkRules();
}


void FireworksDemo::InitFireworkRules() {
	// Go through the firework types and create their m_FRules.
	m_FRules[0].Init(2);
	m_FRules[0].SetParameters(
		1, // type
		0.5f, 1.4f, // age range
		cyclone::Vector3(-5, 25, -5), // min velocity
		cyclone::Vector3(5, 28, 5), // max velocity
		0.1f // damping
		);
	m_FRules[0].m_Payloads[0].Set(3, 5);
	m_FRules[0].m_Payloads[1].Set(5, 5);

	m_FRules[1].Init(1);
	m_FRules[1].SetParameters(
		2, // type
		0.5f, 1.0f, // age range
		cyclone::Vector3(-5, 10, -5), // min velocity
		cyclone::Vector3(5, 20, 5), // max velocity
		0.8f // damping
		);
	m_FRules[1].m_Payloads[0].Set(4, 2);

	m_FRules[2].Init(0);
	m_FRules[2].SetParameters(
		3, // type
		0.5f, 1.5f, // age range
		cyclone::Vector3(-5, -5, -5), // min velocity
		cyclone::Vector3(5, 5, 5), // max velocity
		0.1f // damping
		);

	m_FRules[3].Init(0);
	m_FRules[3].SetParameters(
		4, // type
		0.25f, 0.5f, // age range
		cyclone::Vector3(-20, 5, -5), // min velocity
		cyclone::Vector3(20, 5, 5), // max velocity
		0.2f // damping
		);

	m_FRules[4].Init(1);
	m_FRules[4].SetParameters(
		5, // type
		0.5f, 1.0f, // age range
		cyclone::Vector3(-20, 2, -5), // min velocity
		cyclone::Vector3(20, 18, 5), // max velocity
		0.01f // damping
		);
	m_FRules[4].m_Payloads[0].Set(3, 5);

	m_FRules[5].Init(0);
	m_FRules[5].SetParameters(
		6, // type
		3, 5, // age range
		cyclone::Vector3(-5, 5, -5), // min velocity
		cyclone::Vector3(5, 10, 5), // max velocity
		0.95f // damping
		);

	m_FRules[6].Init(1);
	m_FRules[6].SetParameters(
		7, // type
		4, 5, // age range
		cyclone::Vector3(-5, 50, -5), // min velocity
		cyclone::Vector3(5, 60, 5), // max velocity
		0.01f // damping
		);
	m_FRules[6].m_Payloads[0].Set(8, 10);

	m_FRules[7].Init(0);
	m_FRules[7].SetParameters(
		8, // type
		0.25f, 0.5f, // age range
		cyclone::Vector3(-1, -1, -1), // min velocity
		cyclone::Vector3(1, 1, 1), // max velocity
		0.01f // damping
		);

	m_FRules[8].Init(0);
	m_FRules[8].SetParameters(
		9, // type
		3, 5, // age range
		cyclone::Vector3(-15, 10, -5), // min velocity
		cyclone::Vector3(15, 15, 5), // max velocity
		0.95f // damping
		);
	// ... and so on for other firework types ...
}


void FireworksDemo::Create(uint32_t type, const Firework* parent) {
	m_Fireworks[m_NextFirework] = m_FRules[type - 1].Create(parent);
	
	// Increment the index for the next firework
	m_NextFirework = (m_NextFirework + 1) % MAX_FIREWORKS;
}

void FireworksDemo::Create(uint32_t type, uint32_t number, const Firework* parent) {
	for (size_t i = 0; i < number; ++i) {
		Create(type, parent);
	}
}

void FireworksDemo::Update() {
	// Find the duration of the last frame in seconds
	float duration = static_cast<float>(TimingData::Get().m_LastFrameDuration) * 0.001f;
	if (duration <= 0.0f) return;

	for (auto& firework : m_Fireworks) {
		// Check if we need to process this firework.
		if (firework.m_Type > 0) {
			// Does it need removing?
			if (firework.Update(duration)) {
				// Find the appropriate rule
				const FireworkRule& rule = m_FRules[firework.m_Type - 1];

				// Delete the current firework (this doesn't affect its
				// position and velocity for passing to the create function,
				// just whether or not it is processed for rendering or
				// physics.
				firework.m_Type = 0;

				// Add the payload
				for (size_t i = 0; i < rule.m_PayloadCount; ++i) {
					//const FireworkRule::Payload& payload = rule.m_Payloads[i];
					Create(rule.m_Payloads[i].type, rule.m_Payloads[i].count, &firework);
				}
			}
		}
	}
}

void FireworksDemo::Render() {

	m_Shader->Use();
	m_Shader->SetMat4("projection", projection);
	m_Shader->SetMat4("view", m_Camera->GetViewMatrix());

	// Render each firework in turn
	for (const Firework& firework : m_Fireworks) {
		// Check if we need to process this firework.
		if (firework.m_Type > 0) {
			switch (firework.m_Type) {
			case 1:
				m_Shader->SetVec3("Color", glm::vec3(1.0f, 0.0f, 0.0f));
				break;
			case 2: 
				m_Shader->SetVec3("Color", glm::vec3(1.0f, 0.5f, 0.0f));
				break;
			case 3: 
				m_Shader->SetVec3("Color", glm::vec3(1.0f, 1.0f, 0.0f));
				break;
			case 4: 
				m_Shader->SetVec3("Color", glm::vec3(0.0f, 1.0f, 0.0f));
				break;
			case 5: 
				m_Shader->SetVec3("Color", glm::vec3(0.0f, 1.0f, 1.0f));
				break;
			case 6: 
				m_Shader->SetVec3("Color", glm::vec3(0.4f, 0.4f, 1.0f));
				break;
			case 7: 
				m_Shader->SetVec3("Color", glm::vec3(1.0f, 0.0f, 1.0f));
				break;
			case 8: 
				m_Shader->SetVec3("Color", glm::vec3(1.0f, 1.0f, 1.0f));
				break;
			case 9: 
				m_Shader->SetVec3("Color", glm::vec3(1.0f, 0.5f, 0.5f));
				break;
			};

			const cyclone::Vector3& pos = firework.GetPosition();
			m_Star->ResetModelMatrix();
			m_Star->Translate(glm::vec3(pos.GetX(), pos.GetY(), pos.GetZ()));
			m_Shader->SetMat4("model", m_Star->GetModelMatrix());
			m_Star->Draw(*m_Shader);

			m_Star->ResetModelMatrix();
			m_Star->Translate(glm::vec3(pos.GetX(), -pos.GetY(), pos.GetZ()));
			m_Shader->SetMat4("model", m_Star->GetModelMatrix());
			m_Star->Draw(*m_Shader);
		}
	}
}

void FireworksDemo::ProcessKeyboardInput(int key, int action) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(m_Window, true);
	}
	else if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		Create(1, 1, nullptr);
	}
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		Create(2, 1, nullptr);
	}
	else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		Create(3, 1, nullptr);
	}
	else if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		Create(4, 1, nullptr);
	}
	else if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		Create(5, 1, nullptr);
	}
	else if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
		Create(6, 1, nullptr);
	}
	else if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
		Create(7, 1, nullptr);
	}
	else if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
		Create(8, 1, nullptr);
	}
	else if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
		Create(9, 1, nullptr);
	}

}

void FireworksDemo::InitializeData() {
	m_Shader = std::make_unique<Shader>("res/shaders/quad_vertex.shader", "res/shaders/quad_fragment.shader");
	std::string sourceFilePath = __FILE__;
	std::filesystem::path sourcePath(sourceFilePath);
	std::filesystem::path sourceDirectory = sourcePath.parent_path().parent_path();
	std::filesystem::path shader_dir = sourceDirectory / "res" / "shaders/";
	m_Shader = std::make_unique<Shader>(shader_dir.string() + "quad_vertex.shader",
		shader_dir.string() + "quad_fragment.shader");

	glEnable(GL_DEPTH_TEST);
	m_Camera = std::make_shared<Camera>(glm::vec3(0.0f, 4.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_Star = std::make_unique<Star>(5,0.2f,0.5f);
}


void FireworksDemo::Run() {

	InitializeData();

	while (!glfwWindowShouldClose(m_Window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Render();
		TimingData::Get().Update();
		Update();
		// Swap buffers and poll events
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}
