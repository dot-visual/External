#pragma once
#include "Misc.h"
#include "ProcMemory.h"

void Misc::BunnyHop()
{
	/*
					ProcMemory procMem;
	CLocalPlayer localPlayer;
	int vJump = 5;
	if (GetAsyncKeyState(0x20))
	{
		if(localPlayer.Flags == 257)
		{
			vJump = 5;
		}
		if(localPlayer.Flags == 256)
		{
			vJump = 4;
		}
		procMem.WriteMemory<int>(dwClientDLL + dwForceJump, vJump);
	}
	*/

}

void Misc::SetBhop()
{
	m_bhop = !m_bhop;
}

bool Misc::GetBhop()
{
	return m_bhop;
}