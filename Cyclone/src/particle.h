#pragma once
#include "vector.h"

namespace cyclone {

	class Particle {
	public:
		Particle() = default;
		explicit Particle(const Vector3& position, const Vector3& velocity, const Vector3& acceleration,
			float damping, float mass);

		void Integrate(float duration);

		inline const Vector3& GetPosition() const {
			return m_Position;
		}
		inline const Vector3& GetVelocity() const {
			return m_Velocity;
		}
		inline const Vector3& GetAcceleration() const {
			return m_Acceleration;
		}
		inline const Vector3& GetAccumForce() const {
			return m_AccumulatedForce;
		}

		inline void ClearAccumulator(){
			m_AccumulatedForce.Clear();
		}

		void SetPosition(const Vector3& position);
		void SetVelocity(const Vector3& velocity);
		void SetAcceleration(const Vector3& acceleration);

		void SetPosition(float x,float y, float z);
		void SetVelocity(float v_x,float v_y,float v_z);
		void SetAcceleration(float a_x,float a_y, float a_z);
		
		void SetDamping(float damping);
		void SetMass(float mass);
		void SetInverseMass(float mass);


	protected:
		Vector3 m_Position;
		Vector3 m_Velocity;
		Vector3 m_Acceleration;
		Vector3 m_AccumulatedForce;
		float m_Damping;
		float m_InverseMass;
	};



}

