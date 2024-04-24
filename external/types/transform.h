#pragma once
#include <cstdint>
#include <corecrt_math.h>

// https://www.unknowncheats.me/forum/escape-from-tarkov/618045-rebuilt-transform-methods.html

// optional: use your own vector3/vector4 structs
// IMPORTANT: make sure your multiplication operators are the same, if theyre not you might get funky values

struct vector3
{
	float x, y, z;

	inline vector3 operator*(float rhs) const { return { x * rhs, y * rhs, z * rhs }; }
	inline vector3 operator+(const vector3& rhs) const { return { x + rhs.x, y + rhs.y, z + rhs.z }; }
	inline vector3 operator-(const vector3& rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z }; }
	inline vector3 operator*(const vector3& rhs) const { return { x * rhs.x, y * rhs.y, z * rhs.z }; }
	inline vector3 operator/(const vector3& rhs) const { return { x / rhs.x, y / rhs.y, z / rhs.z }; }
	inline vector3 operator-() const { return { -x, -y, -z }; }

	// normalized
	inline vector3 normalized() const
	{
		float len = sqrtf(x * x + y * y + z * z);
		return { x / len, y / len, z / len };
	}

	std::string toString()
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
	}
};

struct vector4
{
	float x, y, z, w;
	inline vector4 operator*(float rhs) const { return { x * rhs, y * rhs, z * rhs, w * rhs }; }
	inline vector4 operator+(const vector4& rhs) const { return { x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w }; }
	inline vector4 operator-(const vector4& rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w }; }
	inline vector4 operator/(const vector4& rhs) const { return { x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w }; }
	inline vector4 operator-() const { return { -x, -y, -z, -w }; }

	inline vector4 operator*(const vector4& rhs) const
	{
		return {
			w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
			w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z,
			w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x,
			w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z
		};
	}

	inline vector3 operator*(const vector3& rhs) const
	{
		float x = this->x * 2.0F;
		float y = this->y * 2.0F;
		float z = this->z * 2.0F;
		float xx = this->x * x;
		float yy = this->y * y;
		float zz = this->z * z;
		float xy = this->x * y;
		float xz = this->x * z;
		float yz = this->y * z;
		float wx = this->w * x;
		float wy = this->w * y;
		float wz = this->w * z;

		vector3 res;
		res.x = (1.0f - (yy + zz)) * rhs.x + (xy - wz) * rhs.y + (xz + wy) * rhs.z;
		res.y = (xy + wz) * rhs.x + (1.0f - (xx + zz)) * rhs.y + (yz - wx) * rhs.z;
		res.z = (xz - wy) * rhs.x + (yz + wx) * rhs.y + (1.0f - (xx + yy)) * rhs.z;

		return res;
	}

	inline vector4 conjugate() const { return { -x, -y, -z, w }; }
};

class TransformInternal
{
#pragma region Internal Structs
	// make sure these are correct, these are read from memory
	struct TransformAccess
	{
		uintptr_t hierarchyAddr;
		int index;
	};

	class trsX
	{
	public:
		vector3 t;
	private:
		char pad_000C[4];
	public:
		vector4 q;
		vector3 s;
	private:
		char pad_0014[4];
	};
#pragma endregion
#pragma region List
	template <typename T>
	class ResizableBuffer
	{
	public:
		T* buffer;
		int capacity;

		inline ResizableBuffer() : buffer(nullptr), capacity(100)
		{
			buffer = new T[capacity];
		}

		inline void updateBuffer(uintptr_t address, int capacity)
		{
			if (capacity > this->capacity)
			{
				if (buffer)
					delete[] buffer;

				buffer = new T[capacity];
				this->capacity = capacity;
			}

			read_buffer(address, (void*)buffer, sizeof(T) * capacity);
		}

		inline T& operator[](int index)
		{
			if (index >= capacity)
				printf("index out of bounds: forgot to call updateBuffer?\n");
			return buffer[index];
		}
	};
#pragma endregion
	// use the same buffer for all transforms. NOTE: if you're multithreaded, probably mutex these or store buffer another way
	static inline ResizableBuffer<trsX> trsBuffer;
	static inline ResizableBuffer<int> parentIndicesBuffer;

	uintptr_t address;

	TransformAccess transformAccess;
	uintptr_t localTransforms;
	uintptr_t parentIndices;

	// might be beneficial to call these yourself instead of in every function, if you happen to use multiple functions that call this?
	inline void updateTrsXBuffer()
	{
		// feel free to change how new max cap is calc'd. could be index * 2 or something to avoid reallocs
		trsBuffer.updateBuffer(localTransforms, transformAccess.index + 1);
	}

	inline void updateParentIndicesBuffer()
	{
		parentIndicesBuffer.updateBuffer(parentIndices, transformAccess.index + 1);
	}

public:
	inline TransformInternal(uintptr_t address)
	{
		this->address = address;
		this->transformAccess = read<TransformAccess>(address + 0x38);
		this->localTransforms = read<uintptr_t>(transformAccess.hierarchyAddr + 0x18);
		this->parentIndices = read<uintptr_t>(transformAccess.hierarchyAddr + 0x20);
	}

	// ------------------------------
	// actual methods
	// ------------------------------

	inline vector3 localPosition()
	{
		return read<trsX>(localTransforms + transformAccess.index * sizeof(trsX)).t;
	}

	inline vector3 localScale()
	{
		return read<trsX>(localTransforms + transformAccess.index * sizeof(trsX)).s;
	}

	inline vector4 localRotation()
	{
		return read<trsX>(localTransforms + transformAccess.index * sizeof(trsX)).q;
	}

	inline vector3 position()
	{
		updateTrsXBuffer();
		updateParentIndicesBuffer();

		vector3 worldPos = trsBuffer[transformAccess.index].t;
		int index = parentIndicesBuffer[transformAccess.index];
		while (index >= 0)
		{
			auto parent = trsBuffer[index];

			worldPos = parent.q * worldPos;
			worldPos = worldPos * parent.s;
			worldPos = worldPos + parent.t;

			index = parentIndicesBuffer[index];
		}

		return worldPos;
	}

	inline vector4 rotation()
	{
		updateTrsXBuffer();
		updateParentIndicesBuffer();

		vector4 worldRot = trsBuffer[transformAccess.index].q;
		int index = parentIndicesBuffer[transformAccess.index];
		while (index >= 0)
		{
			auto parent = trsBuffer[index];

			worldRot = parent.q * worldRot;

			index = parentIndicesBuffer[index];
		}

		return worldRot;
	}


	inline vector3 right()
	{
		static vector3 right = { 1, 0, 0 };
		return rotation() * right;
	}

	inline vector3 up()
	{
		static vector3 up = { 0, 1, 0 };
		return rotation() * up;
	}

	inline vector3 forward()
	{
		static vector3 forward = { 0, 0, 1 };
		return rotation() * forward;
	}

	// local to world
	inline vector3 TransformDirection(vector3 localDirection)
	{
		return rotation() * localDirection;
	}

	// world to local
	inline vector3 InverseTransformDirection(vector3 worldDirection)
	{
		return rotation().conjugate() * worldDirection;
	}

	// local to world
	inline vector3 TransformPoint(vector3 localPoint)
	{
		updateTrsXBuffer();
		updateParentIndicesBuffer();

		vector3 worldPos = localPoint;
		int index = transformAccess.index;
		while (index >= 0)
		{
			auto parent = trsBuffer[index];

			worldPos = worldPos * parent.s;
			worldPos = parent.q * worldPos;
			worldPos = worldPos + parent.t;

			index = parentIndicesBuffer[index];
		}

		return worldPos;
	}

	// world to local
	inline vector3 InverseTransformPoint(vector3 worldPoint)
	{
		updateTrsXBuffer();
		updateParentIndicesBuffer();

		vector3 worldPos = trsBuffer[transformAccess.index].t;
		vector4 worldRot = trsBuffer[transformAccess.index].q;

		vector3 localScale = trsBuffer[transformAccess.index].s;

		int index = parentIndicesBuffer[transformAccess.index];
		while (index >= 0)
		{
			auto parent = trsBuffer[index];

			worldPos = parent.q * worldPos;
			worldPos = worldPos * parent.s;
			worldPos = worldPos + parent.t;

			worldRot = parent.q * worldRot;

			index = parentIndicesBuffer[index];
		}

		vector3 local = worldRot.conjugate() * (worldPoint - worldPos);
		return local / localScale;

		return worldPos;
	}
};