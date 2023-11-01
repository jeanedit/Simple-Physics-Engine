#include "vector.h"
#include <cmath>
#include <iostream>

namespace cyclone {
	const Vector3 Vector3::GRAVITY = Vector3(0, -9.81f, 0);

	/* constructors */
	Vector3::Vector3() 
		: m_X(0), 
		  m_Y(0), 
		  m_Z(0) 
	{
	}

	Vector3::Vector3(float x, float y, float z) 
		: m_X(x),
		  m_Y(y), 
		  m_Z(z) 
	{
	}

	/* methods */

	void Vector3::Invert() {
		m_X = -m_X;
		m_Y = -m_Y;
		m_Z = -m_Z;
	}

	float Vector3::Magnitude() const {
		return std::sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
	}

	float Vector3::SquareMagnitude() const {
		return m_X * m_X + m_Y * m_Y + m_Z * m_Z;
	}

	void Vector3::Normalize() {
		float magnitude = Magnitude();
		float length_inverted;
		magnitude == 0 ? length_inverted = 1.0f : length_inverted = 1 / magnitude;

		m_X *= length_inverted;
		m_Y *= length_inverted;
		m_Z *= length_inverted;
	}


	void Vector3::AddScaledVector(const Vector3& vector, float scale) {
		(*this) += vector * scale;
	}

	void Vector3::PrintVector() const {
		std::cout << m_X << ' ' << m_Y << ' ' << m_Z << std::endl;
	}

	void Vector3::Clear() {
		m_X = 0.0f;
		m_Y = 0.0f;
		m_Z = 0.0f;
	}

	void Vector3::ComponentProduct(const Vector3& other){
		m_X *= other.m_X;
		m_Y *= other.m_Y;
		m_Z *= other.m_Z;
	}

	Vector3 Vector3::ComponentProduct(const Vector3& other) const {
		return Vector3(m_X * other.m_X, m_Y * other.m_Y, m_Z * other.m_Z);
	}

	float Vector3::DotProduct(const Vector3& other) const {
		return m_X * other.m_X, m_Y* other.m_Y, m_Z* other.m_Z;
	}

	Vector3 Vector3::CrossProduct(const Vector3& other) const {
		return Vector3(m_Y * other.m_Z - m_Z * other.m_Y,
			m_Z * other.m_X - m_X * other.m_Z,
			m_X * other.m_Y - m_Y * other.m_X);
	}

	/* methods end */


	/* overloaded operators */

	Vector3 Vector3::operator+(const Vector3& other) const {
		return Vector3(m_X + other.m_X, m_Y + other.m_Y, m_Z + other.m_Z);
	}

	Vector3 Vector3::operator-(const Vector3& other) const {
		return Vector3(m_X - other.m_X, m_Y - other.m_Y, m_Z - other.m_Z);
	}

	Vector3 Vector3::operator*(float value) const {
		return Vector3(m_X * value, m_Y * value, m_Z * value);
	}


	void Vector3::operator+=(const Vector3& other) {
		m_X += other.m_X;
		m_Y += other.m_Y;
		m_Z += other.m_Z;
	}

	void Vector3::operator-=(const Vector3& other) {
		m_X -= other.m_X;
		m_Y -= other.m_Y;
		m_Z -= other.m_Z;
	}

	void Vector3::operator*=(float value) {
		m_X *= value;
		m_Y *= value;
		m_Z *= value;
	}

	/* Dot product */
	float Vector3::operator*(const Vector3& other) const {
		return m_X * other.m_X + m_Y * other.m_Y + m_Z * other.m_Z;
	}

	/* overloaded operators end  */

	void Vector3::MakeOrthonormalBasis(Vector3& a, Vector3& b, Vector3& c) {
		a.Normalize();
		c = a.CrossProduct(b);
		if (c.SquareMagnitude() == 0.0) {
			return;
		}
		c.Normalize();
		b = c.CrossProduct(b);
	}

}
