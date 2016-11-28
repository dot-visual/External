#include "include.h"
#include "ProcMemory.h"

CLocalPlayer* localPLayer = new CLocalPlayer();

void CLocalPlayer::ReadInformation()
{
		Player = procMem->ReadMemory(offsets->dwClientDLL + offsets->dwLocalPlayer, Player);
		Team = procMem->ReadMemory<int>(Player + offsets->oTeamNum, Team);
		Flags = procMem->ReadMemory<int>(Player + offsets->oFlags, Flags);
		CrosshairID = procMem->ReadMemory<int>(Player + offsets->oCrosshair, CrosshairID);
		
}