#include "Helper.h"
#include "../SDK/Player.h"
#include "../Utils/Utils.h"

namespace Helper {
	uintptr_t GetClientState() {
		return  procMem->ReadMemory<uintptr_t>(Offsets::engineDll + Offsets::dwClientState);
	}

	bool IsValidEnemyIndex(size_t index) {
		return	(entityList[index]->isAlive()) &&
			(!entityList[index]->isLocalPlayer()) &&
			(entityList[index]->getTeam() != localPlayer->getTeam());
	}

	int ClosestEntIndexToPlayer() {
		auto localPlayerPosition = localPlayer->getPos();
		auto clientState = GetClientState();
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

	bool IsIngame() {
		auto ClientState = GetClientState();
		auto state = procMem->ReadMemory<int>(GetClientState() + Offsets::dwClientState_State);
		return state == Utils::SIGNONSTATE_FULL;
	}
}