#include "Aimbot.h"

void Aimbot::SetAimbot(bool state) {
	this->enabled = state;
}

[[nodiscard]] bool Aimbot::GetAimbot() const {
	return this->enabled;
}

void Aimbot::run() {
	if (enabled && GetAsyncKeyState(KEYCODE_RMB)) {
		int bestEnt = Utils::ClosestEntIndexToPlayer();

		if (bestEnt == INVALID_INDEX)
			return;

		auto viewAngles = localPlayer->getViewAngles();
	}
}