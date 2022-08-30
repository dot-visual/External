#ifndef UTILS_HEADER
#define UTILS_HEADER
#include <math.h>

#define M_PI           3.14159265358979323846  /* pi */
#define INVALID_INDEX -1

namespace Utils {

	enum SIGNONSTATE
	{
		SIGNONSTATE_NONE = 0,
		SIGNONSTATE_CHALLENGE = 1,
		SIGNONSTATE_CONNECTED = 2,
		SIGNONSTATE_NEW = 3,
		SIGNONSTATE_PRESPAWN = 4,
		SIGNONSTATE_SPAWN = 5,
		SIGNONSTATE_FULL = 6,
		SIGNONSTATE_CHANGELEVEL = 7
	};

	enum TEAM {
		TEAM_GOTV = 1,
		TEAM_TERRORIST = 2,
		TEAM_COUNTERTERRORIST = 3
	};

	enum FLAGS {
		FL_ONGROUND = 257,
		FL_CROUCHING = 263
	};

	template <typename T>
	T RadToDegrees(T rad) {
		return static_cast<T>((rad * 180 / M_PI));
	}

	template <typename T>
	T DegreesToRad(T deg) {
		return static_cast<T>((deg * M_PI / 180));
	}

	class Vector3 {
	public:
		float x, y, z;

		Vector3() {
			x = y = z = 0.0f;
		}

		Vector3(float X, float Y, float Z) {
			x = X; y = Y; z = Z;
		}

		Vector3(float XYZ) {
			x = XYZ; y = XYZ; z = XYZ;
		}

		Vector3(float* v) {
			x = v[0]; y = v[1]; z = v[2];
		}

		Vector3(const float* v) {
			x = v[0]; y = v[1]; z = v[2];
		}

		inline Vector3& operator=(const Vector3& v) {
			x = v.x; y = v.y; z = v.z; return *this;
		}

		inline Vector3& operator=(const float* v) {
			x = v[0]; y = v[1]; z = v[2]; return *this;
		}

		inline float& operator[](int i) {
			return ((float*)this)[i];
		}

		inline float operator[](int i) const {
			return ((float*)this)[i];
		}

		inline Vector3& operator+=(const Vector3& v) {
			x += v.x; y += v.y; z += v.z; return *this;
		}

		inline Vector3& operator-=(const Vector3& v) {
			x -= v.x; y -= v.y; z -= v.z; return *this;
		}

		inline Vector3& operator*=(const Vector3& v) {
			x *= v.x; y *= v.y; z *= v.z; return *this;
		}

		inline Vector3& operator/=(const Vector3& v) {
			x /= v.x; y /= v.y; z /= v.z; return *this;
		}

		inline Vector3& operator+=(float v) {
			x += v; y += v; z += v; return *this;
		}

		inline Vector3& operator-=(float v) {
			x -= v; y -= v; z -= v; return *this;
		}

		inline Vector3& operator*=(float v) {
			x *= v; y *= v; z *= v; return *this;
		}

		inline Vector3& operator/=(float v) {
			x /= v; y /= v; z /= v; return *this;
		}

		inline Vector3 operator-() const {
			return Vector3(-x, -y, -z);
		}

		inline Vector3 operator+(const Vector3& v) const {
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		inline Vector3 operator-(const Vector3& v) const {
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		inline Vector3 operator*(const Vector3& v) const {
			return Vector3(x * v.x, y * v.y, z * v.z);
		}

		inline Vector3 operator/(const Vector3& v) const {
			return Vector3(x / v.x, y / v.y, z / v.z);
		}

		inline Vector3 operator+(float v) const {
			return Vector3(x + v, y + v, z + v);
		}

		inline Vector3 operator-(float v) const {
			return Vector3(x - v, y - v, z - v);
		}

		inline Vector3 operator*(float v) const {
			return Vector3(x * v, y * v, z * v);
		}

		inline Vector3 operator/(float v) const {
			return Vector3(x / v, y / v, z / v);
		}

		inline float Length() const {
			return sqrtf(x * x + y * y + z * z);
		}

		inline float LengthSqr() const {
			return (x * x + y * y + z * z);
		}

		inline float LengthXY() const {
			return sqrtf(x * x + y * y);
		}

		inline float LengthXZ() const {
			return sqrtf(x * x + z * z);
		}

		inline float DistTo(const Vector3& v) const {
			return (*this - v).Length();
		}

		inline float Dot(const Vector3& v) const {
			return (x * v.x + y * v.y + z * v.z);
		}

		inline Vector3 Cross(const Vector3& v) const {
			return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
		}

		inline bool IsZero() const {
			return (x > -0.01f && x < 0.01f
				&& y > -0.01f && y < 0.01f
				&& z > -0.01f && z < 0.01f);
		}
	};

	class Angle
	{
	public:
		float pitch, yaw, roll;
		Angle(float p_pitch, float p_yaw, float p_roll) :pitch(p_pitch), yaw(p_yaw), roll(p_roll) {};
		Angle() : pitch(0), yaw(0), roll(0) {};

		inline Angle operator-(const Angle& a) const
		{
			return Angle(yaw - a.yaw, pitch - a.pitch, roll - a.roll);
		}

		inline Angle operator*=(const Angle& a) const
		{
			return Angle(yaw * a.yaw, pitch * a.pitch, roll * a.roll);
		}
	};
}

#endif // !UTILS_HEADER
