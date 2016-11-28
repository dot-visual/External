#include "include.h"

Misc* g_pMisc = new Misc();

void Misc::BunnyHop()
{
	int FL_ONGROUND = 257;
	int FL_CROUCHING = 263;
	localPLayer->ReadInformation();
	if(GetAsyncKeyState(0x20))
	{
		if(localPLayer->Flags == FL_ONGROUND || localPLayer->Flags == FL_CROUCHING  )
		{
			int vJump = 6;
			procMem->WriteMemory<int>(offsets->dwClientDLL + offsets->dwForceJump, vJump);
		}
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