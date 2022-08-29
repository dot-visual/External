#include "Misc.h"
#include "../SDK/Player.h"
#include "../Utils/Utils.h"

bool Feature::isEnabled() const {
	return state;
}

void Feature::toggle() {
	state = !state;
}

void Bhop::run() {
	if (!this->isEnabled())
		return;

	if (!GetAsyncKeyState(VK_SPACE))
		return;

	auto flags = localPlayer->getFlags();
	if (flags != Utils::FL_ONGROUND && flags != Utils::FL_CROUCHING)
		return;

	// 6 stands for "invoke once"
	procMem->WriteMemory<int>(Offsets::clientDll + Offsets::dwForceJump, 6);
}

void TriggerBot::run() {
	if (!this->isEnabled())
		return;

	auto crosshairEnt = Player(Utils::GetEntityAddrInCrosshair());
	if (!Utils::IsValidEnemy(crosshairEnt))
		return;
	if (!GetAsyncKeyState(VK_XBUTTON2))
		return;

	// 6 stands for "invoke once"
	procMem->WriteMemory(Offsets::clientDll + Offsets::dwForceAttack, 6);
}