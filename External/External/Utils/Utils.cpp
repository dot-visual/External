#include "Utils.h"
#include "ProcMemory.h"
#include "../SDK/Offsets.h"
#include "../SDK/Player.h"

namespace Utils {
	bool IsValidEnemyIndex(size_t index) {
		return	(entityList[index]->isAlive()) &&
				(!entityList[index]->isLocalPlayer()) &&
				(entityList[index]->getTeam() != localPlayer->getTeam());
	}

	int ClosestEntIndexToPlayer() {
		auto localPlayerPosition = localPlayer->getPos();
		auto clientState = procMem->ReadMemory<uintptr_t>(Offsets::engineDll + Offsets::dwClientState);
		size_t maxPlayers = procMem->ReadMemory<size_t>(clientState + Offsets::dwClientState_MaxPlayer);
		float leastDistance = FLT_MAX;
		int bestIndex = INVALID_INDEX;
		for (size_t i = 0; i < maxPlayers; i++) {
			if (!IsValidEnemyIndex(i))
				continue;

			auto hyp = localPlayer->getPos() - entityList[i]->getPos();
			float distance = hyp.Length();

			if (distance > leastDistance)
				continue;

			leastDistance = distance;
			bestIndex = i;
		}
		return bestIndex;
	}
}