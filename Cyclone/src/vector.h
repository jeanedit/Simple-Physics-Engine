


namespace cyclone {

	class Vector3 {
	public:
		Vector3();
		explicit Vector3(float x, float y, float z);

		void Invert();
		float Magnitude() const;
		float SquareMagnitude() const;
		void Normalize();


		void AddScaledVector(const Vector3& vector, float scale);
		void PrintVector() const;
		void Clear();

		void ComponentProduct(const Vector3& other);
		Vector3 ComponentProduct(const Vector3& other) const;
		float DotProduct(const Vector3& other) const;

		Vector3 CrossProduct(const Vector3& other) const;

		Vector3 operator+(const Vector3& other) const;
		Vector3 operator-(const Vector3& other) const;
		Vector3 operator*(float value) const;


		void operator+=(const Vector3& other);
		void operator-=(const Vector3& other);
		void operator*=(float value);

		/* Dot product */
		float operator*(const Vector3& other) const;

		static void MakeOrthonormalBasis(Vector3& a, Vector3& b, Vector3& c);
		
		inline float GetX() const {
			return m_X;
		}
		inline float GetY() const {
			return m_Y;
		}
		inline float GetZ() const {
			return m_Z;
		}

		inline void SetX(float x){
			m_X = x;
		}
		inline void SetY(float y) {
			m_Y = y;
		}
		inline void SetZ(float z) {
			m_Z = z;
		}

		static const Vector3 GRAVITY;

	private:
		float m_X, m_Y, m_Z;
		float pad = 0.0f; //padding for alignment

	};



}