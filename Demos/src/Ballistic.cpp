#include "Ballistic.h"

#include <algorithm>
#include <filesystem>


glm::vec3 BallisticDemo::lightPos = glm::vec3(1.0f, 0.0f, 2.0f);
glm::mat4 BallisticDemo::projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 1.0f, 600.0f);

void BallisticDemo::AmmoRound::Render(const Shader& shader) {
	cyclone::Vector3 position;
	position = particle.GetPosition();

	shader.Use();
	sphere->ResetModelMatrix();
	sphere->Translate(glm::vec3(position.GetX(), position.GetY(), position.GetZ()));
	sphere->Scale(glm::vec3(3.0f, 3.0f, 3.0f));

	shader.SetMat4("model", sphere->GetModelMatrix());

	// Set lighting parameters (light position, object color, light color)
	shader.SetVec3("lightPos", glm::vec3(lightPos.x, lightPos.y, lightPos.z));
	//shader.SetVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.0f));
	shader.SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

	// Render the sphere
	sphere->Draw(shader);

	// Shadow of the sphere

	sphere->ResetModelMatrix();
	sphere->Translate(glm::vec3(position.GetX(), 0.0f, position.GetZ()));
	sphere->Scale(glm::vec3(3.0f, 3.0f, 3.0f));
	sphere->Scale(glm::vec3(1.0f, 0.1f, 1.0f));
	shader.SetMat4("model", sphere->GetModelMatrix());
	shader.SetVec3("objectColor", glm::vec3(0.75f, 0.75f, 0.75f));
	shader.SetVec3("lightColor", glm::vec3(0.0f, 0.0f, 0.0f));
	sphere->Draw(shader);
}

void BallisticDemo::ProcessKeyboardInput(int key, int action) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(m_Window, true);
	}
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		Fire();
	}

	else if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		m_CurrentShotType = ShotType::PISTOL;
	}
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		m_CurrentShotType = ShotType::ARTILLERY;
	}
	else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		m_CurrentShotType = ShotType::FIREBALL;
	}
	else if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		m_CurrentShotType = ShotType::LASER;
	}
}


void BallisticDemo::Fire() {
	auto shot_it = std::find_if(m_Ammo.begin(), m_Ammo.end(), [](const AmmoRound& shot) {
		return shot.shot_type == ShotType::UNUSED;
		}
	);
	if (shot_it == m_Ammo.end()) {
		return;
	}
	// Set the properties of the particle
	switch (m_CurrentShotType) {
	case ShotType::PISTOL:
		shot_it->particle.SetMass(2.0f); // 2.0kg
		shot_it->particle.SetVelocity(0.0f, 0.0f, -35.0f); // 35m/s
		shot_it->particle.SetAcceleration(0.0f, -1.0f, 0.0f);
		shot_it->particle.SetDamping(0.99f);
		break;

	case ShotType::ARTILLERY:
		shot_it->particle.SetMass(200.0f); // 200.0kg
		shot_it->particle.SetVelocity(0.0f, 30.0f, -40.0f); // 50m/s
		shot_it->particle.SetAcceleration(0.0f, -20.0f, 0.0f);
		shot_it->particle.SetDamping(0.99f);
		break;

	case ShotType::FIREBALL:
		shot_it->particle.SetMass(1.0f); // 1.0kg - mostly blast damage
		shot_it->particle.SetVelocity(0.0f, 0.0f, -10.0f); // 5m/s
		shot_it->particle.SetAcceleration(0.0f, 0.6f, 0.0f); // Floats up
		shot_it->particle.SetDamping(0.9f);
		break;

	case ShotType::LASER:
		// Note that this is the kind of laser bolt seen in films,
		// not a realistic laser beam!
		shot_it->particle.SetMass(0.1f); // 0.1kg - almost no weight
		shot_it->particle.SetVelocity(0.0f, 0.0f, -100.0f); // 100m/s
		shot_it->particle.SetAcceleration(0.0f, 0.0f, 0.0f); // No gravity
		shot_it->particle.SetDamping(0.99f);
		break;
	}

	// Set the data common to all particle types
	shot_it->particle.SetPosition(0.0f, 15.0f, 0.0f);
	shot_it->start_time = TimingData::Get().m_LastFrameTimeStamp;
	shot_it->shot_type = m_CurrentShotType;

	// Clear the force accumulators
	shot_it->particle.ClearAccumulator();
}


void BallisticDemo::RenderStartSphere() {
	m_StrToShader.at("sphere")->Use();

	m_StrToShader.at("sphere")->SetMat4("projection", projection);
	m_StrToShader.at("sphere")->SetMat4("view", m_Camera->GetViewMatrix());

	m_Sphere->ResetModelMatrix();
	m_Sphere->Translate(glm::vec3(0.0f, 15.0f, 0.0f));

	m_StrToShader.at("sphere")->SetMat4("model", m_Sphere->GetModelMatrix());

	// Set lighting parameters (light position, object color, light color)
	m_StrToShader.at("sphere")->SetVec3("lightPos", glm::vec3(lightPos.x, lightPos.y, lightPos.z));
	m_StrToShader.at("sphere")->SetVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.0f));
	m_StrToShader.at("sphere")->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

	// Render the sphere
	m_Sphere->Draw(*m_StrToShader["sphere"]);

	// Shadow of the sphere

	m_Sphere->ResetModelMatrix();
	m_Sphere->Translate(glm::vec3(0.0f, 0.0f, 0.0f));
	m_Sphere->Scale(glm::vec3(1.0f, 0.1f, 1.0f));
	m_StrToShader.at("sphere")->SetMat4("model", m_Sphere->GetModelMatrix());
	m_StrToShader.at("sphere")->SetVec3("objectColor", glm::vec3(0.75f, 0.75f, 0.75f));
	m_StrToShader.at("sphere")->SetVec3("lightColor", glm::vec3(0.0f, 0.0f, 0.0f));
	m_Sphere->Draw(*m_StrToShader.at("sphere"));

}


void BallisticDemo::RenderLines(const VertexArray& vao, size_t ibo_size) {
	m_StrToShader["line"]->Use();
	vao.Bind();
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 1.0f, 1000.0f);
	static const float divisor = 15.0f;
	//glm::mat4 projection = glm::ortho(-(800.0f / divisor), 800.0f / divisor,
	//	600.0f / divisor, -(600.0f / divisor),
	//	1.0f, 500.0f);
	//glm::mat4 projection = glm::mat4(1.0f);
	m_StrToShader["line"]->SetMat4("projection", projection);
	m_StrToShader["line"]->SetMat4("view", m_Camera->GetViewMatrix());
	for (float i = -200.0f; i < 100.0f; i += 10.0f) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -i * 2.0f));
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 30.0f, 1.0f));
		m_StrToShader["line"]->SetMat4("model", model);
		glDrawElements(GL_TRIANGLES, ibo_size, GL_UNSIGNED_INT, 0);
	}
	vao.Unbind();
}

void BallisticDemo::Update() {
	static const uint64_t time_bound = 5000;
	static const float z_bound = -200.0f;
	static const float y_bound = 0.0f;
	// Find the duration of the last frame in seconds
	float duration = static_cast<float>(TimingData::Get().m_LastFrameDuration * 0.001f);

	if (duration <= 0.0f) return;

	for (auto& shot : m_Ammo) {
		if (shot.shot_type != ShotType::UNUSED) {
			// Run the physics
			shot.particle.Integrate(duration);
			// Check if the particle is now invalid
			if (shot.particle.GetPosition().GetY() < y_bound ||
				shot.start_time + time_bound < TimingData::Get().m_LastFrameTimeStamp ||
				shot.particle.GetPosition().GetZ() < z_bound) {
				// We simply set the shot type to be unused, so the
				// memory it occupies can be reused by another shot.
				shot.shot_type = ShotType::UNUSED;
			}
		}
	}
}


void BallisticDemo::Render() {

	RenderStartSphere();

	for (auto& shot : m_Ammo) {
		if (shot.shot_type != ShotType::UNUSED) {
			switch (shot.shot_type) {
			case ShotType::PISTOL:
				m_StrToShader.at("sphere")->SetVec3("objectColor", glm::vec3(1.0f, 0.75f, 0.0f));
				break;
			case ShotType::ARTILLERY:
				m_StrToShader.at("sphere")->SetVec3("objectColor", glm::vec3(0.0f, 0.0f, 0.0f));
				break;

			case ShotType::FIREBALL:
				m_StrToShader.at("sphere")->SetVec3("objectColor", glm::vec3(1.0f, 0.0f, 0.0f));
				break;

			case ShotType::LASER:
				m_StrToShader.at("sphere")->SetVec3("objectColor", glm::vec3(0.2f, 0.7f, 1.0f));
				break;
			}
			shot.Render(*m_StrToShader.at("sphere"));
		}
	}

}


void BallisticDemo::InitializeData() {
	std::string sourceFilePath = __FILE__;
	std::filesystem::path sourcePath(sourceFilePath);
	std::filesystem::path sourceDirectory = sourcePath.parent_path().parent_path();
	std::filesystem::path shader_dir = sourceDirectory / "res"/ "shaders/";
	std::cout << shader_dir.string() + "\\sphere_vertex.shader" << std::endl;
	m_StrToShader["sphere"] = std::make_shared<Shader>(shader_dir.string() + "sphere_vertex.shader", 
		shader_dir.string() + "sphere_fragment.shader");

	m_StrToShader["line"] = std::make_shared<Shader>(shader_dir.string() + "line_vertex.shader", 
		shader_dir.string() + "line_fragment.shader");

	glEnable(GL_DEPTH_TEST);
	m_Camera = std::make_shared<Camera>(glm::vec3(-55.0f, 20.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f), -40.0f, -5.0f);
}

void BallisticDemo::Run() {
	InitializeData();
	//Sphere sphere(2.0f, 36, 36);
	m_Sphere = std::make_shared<Sphere>(2.0f, 36, 36);
	float counter = 0.0f;
	for (auto shot_it = m_Ammo.begin(); shot_it != m_Ammo.end(); std::advance(shot_it, 1)) {
		shot_it->sphere = m_Sphere;
	}

	std::vector<float> groundVertices = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	std::vector<unsigned int> groundIndices = {
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	VertexArray vao;
	vao.Bind();
	VertexBuffer vbo(groundVertices.data(), static_cast<uint32_t>(groundVertices.size()) * sizeof(float));
	IndexBuffer ibo(groundIndices.data(), static_cast<uint32_t>(groundIndices.size()) * sizeof(uint32_t));

	VertexBufferLayout vbl;
	vbl.Push<float>(3);

	vao.AddBuffer(vbo, vbl);
	vao.Unbind();

	while (!glfwWindowShouldClose(m_Window)) {
		glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//ProcessInput();

		Render();
		RenderLines(vao,groundIndices.size());
		TimingData::Get().Update();
		Update();
		// Swap buffers and poll events
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}