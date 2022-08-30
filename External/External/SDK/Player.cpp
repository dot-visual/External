#include "Player.h"
#include "Helper.h"

LocalPlayer* localPlayer;
std::vector<Player*> entityList{};

Player::Player(uintptr_t playerBase) : playerBaseAddr(playerBase) {}

[[nodiscard]] bool Player::isImmune() const {
	return procMem->ReadMemory<int>(playerBaseAddr + Offsets::m_bGunGameImmunity) == 1;
}

[[nodiscard]] bool Player::isAlive() const {
	return procMem->ReadMemory<int>(playerBaseAddr + Offsets::m_iHealth) > 1;
}

[[nodiscard]] UINT Player::getTeam() const {
	return procMem->ReadMemory<unsigned int>(playerBaseAddr + Offsets::m_iTeamNum);
}

[[nodiscard]] bool Player::isDormant() const {
	return procMem->ReadMemory<int>(playerBaseAddr + Offsets::m_bDormant) == 1;
}

[[nodiscard]] Utils::Vector3 Player::getPosition() const {
	return procMem->ReadMemory<Utils::Vector3>(playerBaseAddr + Offsets::m_vecOrigin);
}

[[nodiscard]] int Player::getHealth() const {
	return procMem->ReadMemory<int>(this->playerBaseAddr + Offsets::m_iHealth);
}

[[nodiscard]] int Player::getFlags() const {
	return procMem->ReadMemory<int>(this->playerBaseAddr + Offsets::m_fFlags);
}

[[nodiscard]] Utils::Vector3 Player::getPos() const {
	return procMem->ReadMemory<Utils::Vector3>(this->playerBaseAddr + Offsets::m_vecOrigin);
}

[[nodiscard]] Utils::Vector3 Player::getEyePos() const {
	auto position = this->getPos();
	auto viewOffset = procMem->ReadMemory<Utils::Vector3>(this->playerBaseAddr + Offsets::m_vecViewOffset);
	return position + viewOffset;
}

[[nodiscard]] uintptr_t Player::getAddress() const {
	return this->playerBaseAddr;
}

[[nodiscard]] bool Player::isLocalPlayer() const {
	return procMem->ReadMemory<bool>(playerBaseAddr + Offsets::m_bIsLocalPlayer);
}

[[nodiscard]] bool Player::IsValidEnemy() const {
	return	(this->isAlive()) &&
		(!this->isLocalPlayer()) &&
		(this->getTeam() != localPlayer->getTeam());
}

LocalPlayer::LocalPlayer() {
	this->playerBaseAddr = procMem->ReadMemory<uintptr_t>(Offsets::clientDll + Offsets::dwLocalPlayer);
}

[[nodiscard]] Utils::Angle LocalPlayer::getViewAngles() const {
	auto clientState = Helper::GetClientState();
	return procMem->ReadMemory<Utils::Angle>(clientState + Offsets::dwClientState_ViewAngles);
}
void LocalPlayer::setViewAngles(Utils::Angle angles) const {
	auto clientState = procMem->ReadMemory<uintptr_t>(Offsets::engineDll + Offsets::dwClientState);
	procMem->WriteMemory<Utils::Angle>(clientState + Offsets::dwClientState_ViewAngles, angles);
}

void LocalPlayer::shoot() const {
	procMem->WriteMemory<int>(Offsets::clientDll + Offsets::dwForceAttack, 6);
}

[[nodiscard]] int LocalPlayer::getCrosshairID() const {
	return procMem->ReadMemory<int>(playerBaseAddr + Offsets::m_iCrosshairId);
}

[[nodiscard]] Player LocalPlayer::getEntityInCrosshair() const {
	auto playerAddr = procMem->ReadMemory<uintptr_t>(Offsets::clientDll + Offsets::dwEntityList + ((localPlayer->getCrosshairID() - 1) * Offsets::entityLoopDist));
	return Player(playerAddr);
}