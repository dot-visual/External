#include "Misc.h"
#include "../SDK/Player.h"
#include "../Utils/Utils.h"

#define INVOKE_ONCE 6


Bhop bhop;
TriggerBot triggerBot;

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

	procMem->WriteMemory<int>(Offsets::clientDll + Offsets::dwForceJump, INVOKE_ONCE);
}

void TriggerBot::run() {
	if (!this->isEnabled())
		return;
	if (!localPlayer->getEntityInCrosshair().IsValidEnemy())
		return;
	if (!GetAsyncKeyState(VK_XBUTTON2))
		return;

	procMem->WriteMemory(Offsets::clientDll + Offsets::dwForceAttack, INVOKE_ONCE);
}