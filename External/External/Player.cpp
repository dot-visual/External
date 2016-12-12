#include "include.h"
#include "ProcMemory.h"

CLocalPlayer* localPLayer = new CLocalPlayer();

void CLocalPlayer::ReadInformation()
{
	Player = procMem->ReadMemory(offsets->dwClientDLL + offsets->dwLocalPlayer, Player);

	Team = procMem->ReadMemory<int>(Player + offsets->oTeamNum, Team);
	Flags = procMem->ReadMemory<int>(Player + offsets->oFlags, Flags);
	CrosshairID = procMem->ReadMemory<int>(Player + offsets->oCrosshair, CrosshairID);
	Position[0] = procMem->ReadMemory<float>(Player + offsets->m_vecOrigin);
	Position[1] = procMem->ReadMemory<float>(Player + offsets->m_vecOrigin + 0x4);
	Position[2] = procMem->ReadMemory<float>(Player + offsets->m_vecOrigin + 0x8);
	eyePos = procMem->ReadMemory<float>(Player + 0x10C);
	origin[0] = procMem->ReadMemory<float>(Player + 0x104);
	origin[1] = procMem->ReadMemory<float>(Player + 0x104);
	origin[2] = procMem->ReadMemory<float>(Player + 0x10C);
	view = procMem->ReadMemory<float>(Player + 0x104);
	DWORD baseBones;
	baseBones = procMem->ReadMemory<DWORD>(Player + 0x2698);
	localBones[0] = procMem->ReadMemory<float>(baseBones + 0x30 * 10 + 0xC);
	localBones[1] = procMem->ReadMemory<float>(baseBones + 0x30 * 10 + 0x1C);
	localBones[2] = procMem->ReadMemory<float>(baseBones + 0x30 * 10 + 0x2C);
}

bool CPlayer::isAlive()
{
	return(CPlayer::Health > 1);
}