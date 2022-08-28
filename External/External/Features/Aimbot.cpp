#include "Aimbot.h"
#define KEYCODE_RMB 0x01
#define INVALID_INDEX -1

void Aimbot::SetAimbot(bool state) {
	this->enabled = state;
}

[[nodiscard]] bool Aimbot::GetAimbot() const {
	return this->enabled;
}

void Aimbot::run() {
	if (enabled && GetAsyncKeyState(KEYCODE_RMB)) {
		int bestEnt = 1; // Utils::ClosestEntIndexToPlayer();

		if (bestEnt == INVALID_INDEX)
			return;

	}
}