#include "Player.h"

Player::Player(uintptr_t playerBase) : playerBaseAddr(playerBase) {}

[[nodiscard]] bool Player::isImmune() const {
	return procMem->ReadMemory<int>(playerBaseAddr + Offsets::m_bGunGameImmunity) == 1;
}

[[nodiscard]] bool Player::isAlive() const {
	return procMem->ReadMemory<int>(playerBaseAddr + Offsets::m_iHealth) > 1;
}

[[nodiscard]] unsigned int Player::getTeam() const {
	return procMem->ReadMemory<unsigned int>(playerBaseAddr + Offsets::m_iTeamNum);
}

[[nodiscard]] bool Player::isDormant() const {
	return procMem->ReadMemory<int>(playerBaseAddr + Offsets::m_bDormant) == 1;
}

[[nodiscard]] Utils::Vector3 Player::getPosition() const {
	return procMem->ReadMemory<Utils::Vector3>(playerBaseAddr + Offsets::m_vecOrigin);
}

LocalPlayer& LocalPlayer::GetInstance()
{
	static LocalPlayer instance;
	return instance;
}

[[nodiscard]] uintptr_t LocalPlayer::getAddress() const {
	return procMem->ReadMemory<uintptr_t>(Offsets::clientDll + Offsets::dwLocalPlayer);
}
//int getHealth() const;
//int getFlags() const;
//Utils::Vector3 getPos() const;
//Utils::Vector3 getEyePos() const;
//Utils::Vector3 getViewAngle() const;

[[nodiscard]] int LocalPlayer::getHealth() const {
	return procMem->ReadMemory<int>(Offsets::dwLocalPlayer + Offsets::m_iHealth);
}

[[nodiscard]] int LocalPlayer::getFlags() const {
	return procMem->ReadMemory<int>(Offsets::dwLocalPlayer + Offsets::m_fFlags);
}

[[nodiscard]] Utils::Vector3 LocalPlayer::getPos() const {
	return procMem->ReadMemory<Utils::Vector3>(Offsets::dwLocalPlayer + Offsets::m_vecOrigin);
}

[[nodiscard]] Utils::Vector3 LocalPlayer::getEyePos() const {
	auto position = this->getPos();
	auto viewOffset = procMem->ReadMemory<Utils::Vector3>(Offsets::dwLocalPlayer + Offsets::m_vecViewOffset);
	return position + viewOffset;
}

[[nodiscard]] Utils::Vector3 LocalPlayer::getViewAngle() const {
	auto clientState = procMem->ReadMemory<uintptr_t>(Offsets::engineDll + Offsets::dwClientState);
	return procMem->ReadMemory<Utils::Vector3>(clientState + Offsets::dwClientState_ViewAngles);
}