#include "unity.h"
#include <emmintrin.h>

namespace Unity
{
	addfield(Vector3, Transform, position, 0x90);

	Transform* GameObject::transform() // credit: frankie-11
	{
		auto components = read<uintptr_t>(thisptr + 0x30);
		return (Transform*)read<uintptr_t>(read<uintptr_t>(components + 0x8) + 0x38);
	}
}