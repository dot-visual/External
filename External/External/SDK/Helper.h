#pragma once
#ifndef HELPER_HEADER
#define HELPER_HEADER
#include <cstdint>

namespace Helper {
	bool IsValidEnemyIndex(size_t index);
	bool IsIngame();
	int ClosestEntIndexToPlayer();
	uintptr_t GetClientState();
}

#endif // !HELPER_HEADER


