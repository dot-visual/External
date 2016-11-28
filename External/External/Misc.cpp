#include "include.h"

Misc* g_pMisc = new Misc();

void Misc::BunnyHop()
{
	localPLayer->ReadInformation();
	int vJump = 5;
	if (GetAsyncKeyState(0x20))
	{
		if(localPLayer->Flags == 257)
		{
			vJump = 5;
		}
		if(localPLayer->Flags == 256)
		{
			vJump = 4;
		}
		procMem->WriteMemory<int>(offsets->dwClientDLL + offsets->dwForceJump, vJump);
	}
}

void Misc::SetBhop()
{
	m_bhop = !m_bhop;
}

bool Misc::GetBhop()
{
	return m_bhop;
}