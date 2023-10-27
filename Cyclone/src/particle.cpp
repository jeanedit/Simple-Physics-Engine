#include "particle.h"
#include <cassert>
#include <cmath>

namespace cyclone {

	Particle::Particle(const Vector3& position, const Vector3& velocity, const Vector3& acceleration, float damping, float mass)
		: m_Position(position),
		m_Velocity(velocity),
		m_Acceleration(acceleration),
		m_Damping(damping),
		m_InverseMass(1.0f)
	{
		assert(mass > 0.0f);
		m_InverseMass = 1.0f / mass;
	}

	void Particle::Integrate(float duration) {
		if (m_InverseMass <= 0.0f) {
			return;
		}
		assert(duration > 0.0f);
		// Update linear position.
		m_Position.AddScaledVector(m_Velocity, duration);

		// Update linear velocity from the acceleration.
		m_Velocity.AddScaledVector(m_Acceleration, duration);
		// Impose drag.
		m_Velocity *= std::pow(m_Damping, duration);
		// Clear the forces.
		m_AccumulatedForce.Clear();
	}


	void Particle::SetPosition(const Vector3& position) {
		m_Position = position;
	}
	void Particle::SetVelocity(const Vector3& velocity) {
		m_Velocity = velocity;
	}
	void Particle::SetAcceleration(const Vector3& acceleration) {
		m_Acceleration = acceleration;
	}

	void Particle::SetPosition(float x, float y, float z){
		m_Position.SetX(x);
		m_Position.SetY(y);
		m_Position.SetZ(z);
	}

	void Particle::SetVelocity(float v_x, float v_y, float v_z) {
		m_Velocity.SetX(v_x);
		m_Velocity.SetY(v_y);
		m_Velocity.SetZ(v_z);
	}
	void Particle::SetAcceleration(float a_x, float a_y, float a_z) {
		m_Acceleration.SetX(a_x);
		m_Acceleration.SetY(a_y);
		m_Acceleration.SetZ(a_z);
	}

	void Particle::SetDamping(float damping) {
		m_Damping = damping;
	}
	void Particle::SetMass(float mass) {
		assert(mass > 0.0f);
		m_InverseMass = 1.0f / mass;
	}
	void Particle::SetInverseMass(float inverse_mass) {
		m_InverseMass = inverse_mass;
	}

}
