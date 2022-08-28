#ifndef OFFSETS_HEADER
#define OFFSETS_HEADER
#include "../Includes.h"

namespace Offsets {
	uintptr_t clientDll{};
	uintptr_t engineDll{};
	constexpr uintptr_t m_bGunGameImmunity = 0x0;
	constexpr uintptr_t m_iTeamNum = 0x0;
	constexpr uintptr_t m_iHealth = 0x100;
	constexpr uintptr_t m_bDormant = 0xED;
	constexpr uintptr_t m_vecOrigin = 0x138;
	constexpr uintptr_t m_fFlags = 0x104;
	constexpr uintptr_t m_vecViewOffset = 0x108;
	constexpr uintptr_t m_bIsLocalPlayer = 0x3628;
	constexpr uintptr_t dwLocalPlayer = 0xDC14BC;
	constexpr uintptr_t dwEntityList = 0x4DDD92C;
	constexpr uintptr_t dwClientState = 0x58CFDC;
	constexpr uintptr_t dwClientState_GetLocalPlayer = 0x180;
	constexpr uintptr_t dwClientState_ViewAngles = 0x4D90;
	constexpr uintptr_t dwClientState_MaxPlayer = 0x388;
	constexpr uintptr_t dwClientState_PlayerInfo = 0x52C0;
}

#endif // !OFFSETS_HEADER
