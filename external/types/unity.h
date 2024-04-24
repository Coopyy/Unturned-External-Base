#ifndef UNITY_H
#define UNITY_H

#include "../unturned.h"
#include "transform.h"

namespace Unity
{
	class Transform;
	class GameObject;

	template <typename T>
	class Array
	{
	public:
		inline uint32_t Count()
		{
			return read<uint32_t>(THISPTR + 0x18);
		}

		inline T Get(uint32_t index)
		{
			return read<T>(read<uintptr_t>(THISPTR + 0x10) + 0x20 + (index * sizeof(T)));
		}

		// youd prob want a method to just read the whole array into a vector here
	};

	class GameObject
	{
	public:
		TransformInternal transform();
	};
}

#endif