#include "unity.h"
#include <emmintrin.h>

namespace Unity
{
	FIELD_DEF(Vector3, Transform, localPosition, 0x90);

	Transform* GameObject::transform() // credit: frankie-11
	{
		auto components = read<uintptr_t>(THISPTR + 0x30);
		return (Transform*)read<uintptr_t>(read<uintptr_t>(components + 0x8) + 0x38);
	}
}