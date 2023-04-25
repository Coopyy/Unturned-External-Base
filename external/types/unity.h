#ifndef UNITY_H
#define UNITY_H

#include "../unturned.h"

namespace Unity
{
	class Transform;
	class GameObject;


	class Vector3
	{
	public:
		Vector3() : x(0.f), y(0.f), z(0.f)
		{

		}

		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
		{

		}
		~Vector3()
		{

		}

		float x;
		float y;
		float z;

		inline float Dot(Vector3 v)
		{
			return x * v.x + y * v.y + z * v.z;
		}

		inline float Distance(Vector3 v)
		{
			return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
		}
		inline float Length()
		{
			float ls = x * x + y * y + z * z;
			return sqrt(ls);
		}


		bool operator==(const Vector3& in) const
		{
			return (this->x == in.x && this->y == in.y && this->z == in.z);
		}

		Vector3 operator+(Vector3 v)
		{
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		Vector3 operator-(Vector3 v)
		{
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		Vector3 operator*(float number) const
		{
			return Vector3(x * number, y * number, z * number);
		}

		Vector3& operator/=(float fl)
		{
			x /= fl;
			y /= fl;
			z /= fl;
			return *this;
		}

		Vector3& operator-=(const Vector3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return *this;
		}

		std::string ToString()
		{
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
		}
	};

	class Transform
	{
	public:
		Field<Vector3>* position();
	};

	class GameObject
	{
	public:
		Transform* transform();
	};
}

#endif