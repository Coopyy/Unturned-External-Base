#include "unity.h"
#include <emmintrin.h>

namespace Unity
{
	TransformInternal GameObject::transform()
	{
		auto components = read<uintptr_t>(THISPTR + 0x30);
		return TransformInternal(read<uintptr_t>(components + 0x8));
	}
}