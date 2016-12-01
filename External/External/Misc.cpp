#include "include.h"

Misc* g_pMisc = new Misc();

void Misc::BunnyHop()
{
	if(GetBhop())
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
}

void Misc::SetBhop()
{
	m_bhop = !m_bhop;
}

bool Misc::GetBhop()
{
	return m_bhop;
}

void Misc::SetTrigger()
{
	m_trigger = !m_trigger;
}

bool Misc::GetTrigger()
{
	return m_trigger;
}

void Misc::SetGlow()
{
	m_glow = !m_glow;
}

bool Misc::GetGlow()
{
	return m_glow;
}

void Misc::Triggerbot()
{
	if(GetTrigger())
	{
		localPLayer->ReadInformation();
		CPlayer enemyPlayer;
		enemyPlayer.Player = procMem->ReadMemory<DWORD>(offsets->dwClientDLL + offsets->aEntityList + ((localPLayer->CrosshairID - 1) * offsets->oEntityLoopDist), localPLayer->enemyInCH);
		enemyPlayer.Health = procMem->ReadMemory<int>(enemyPlayer.Player + offsets->oHealth);
		enemyPlayer.Team = procMem->ReadMemory<int>(enemyPlayer.Player + offsets->oTeamNum);
		if(GetAsyncKeyState(VK_RBUTTON) && enemyPlayer.isAlive() && enemyPlayer.Team != localPLayer->Team)
		{
			int vAtk = 6;
			procMem->WriteMemory(offsets->dwClientDLL + offsets->dwForceAttack, vAtk);

			Sleep(250);
		}
	}
}

Misc::~Misc()
{
}

Misc::Misc()
{
	m_bhop = false;
	m_glow = false;
	m_trigger = false;
	GlowTerroristRed = 1.f;
	GlowTerroristGreen = 0.f;
	GlowTerroristBlue = 0.f;
	GlowTerroristAlpha = 1.f;
	m_bRenderWhenOccluded = true;
	m_bRenderWhenUnoccluded = false;
}

void Misc::Glow()
{
	if(GetGlow())
	{
		//GlowStruct CTglow = {0.0f, 0.0f, 1.0f, 1.0f, true, false};
		bool GlowActive = true;
		bool GlowTeamCheck = true;
		DWORD someOffset = 0x38;
		DWORD glow_Pointer;
		glow_Pointer = procMem->ReadMemory(offsets->dwClientDLL + 0x4FD91C4, glow_Pointer);

		for (int i = 0; i < 32; i++)
		{
			int glow_currentPlayer = procMem->ReadMemory<int>(offsets->dwClientDLL + offsets->aEntityList + i * offsets->oEntityLoopDist ,glow_currentPlayer);
			int glow_currentPlayerGlowIndex = procMem->ReadMemory<int>(glow_currentPlayer + 0xA320 ,glow_currentPlayerGlowIndex);
			int EntityBaseTeamID = procMem->ReadMemory<int>(glow_currentPlayer + offsets->oTeamNum, EntityBaseTeamID);

			if (localPLayer->Team != EntityBaseTeamID || GlowTeamCheck == false)
				switch (EntityBaseTeamID)	// 1 GoTV; 2 T; 3 CT
			{
				case 2:
					procMem->WriteMemory<float>((glow_Pointer + ((glow_currentPlayerGlowIndex * someOffset) + 0x4)), GlowTerroristRed);
					procMem->WriteMemory<float>((glow_Pointer + ((glow_currentPlayerGlowIndex * someOffset) + 0x8)), GlowTerroristGreen);
					procMem->WriteMemory<float>((glow_Pointer + ((glow_currentPlayerGlowIndex * someOffset) + 0xC)), GlowTerroristBlue);
					procMem->WriteMemory<float>((glow_Pointer + ((glow_currentPlayerGlowIndex * someOffset) + 0x10)), GlowTerroristAlpha);
					procMem->WriteMemory<BOOL>((glow_Pointer + ((glow_currentPlayerGlowIndex * someOffset) + 0x24)), m_bRenderWhenOccluded);
					procMem->WriteMemory<BOOL>((glow_Pointer + ((glow_currentPlayerGlowIndex * someOffset) + 0x25)), m_bRenderWhenUnoccluded);
					break;
				case 3:
					procMem->WriteMemory<float>((glow_Pointer + ((glow_currentPlayerGlowIndex * someOffset) + 0x4)), (GlowTerroristRed - 1.f));
					procMem->WriteMemory<float>((glow_Pointer + ((glow_currentPlayerGlowIndex * someOffset) + 0x8)), GlowTerroristGreen);
					procMem->WriteMemory<float>((glow_Pointer + ((glow_currentPlayerGlowIndex * someOffset) + 0xC)), (GlowTerroristBlue + 1.f));
					procMem->WriteMemory<float>((glow_Pointer + ((glow_currentPlayerGlowIndex * someOffset) + 0x10)), GlowTerroristAlpha);
					procMem->WriteMemory<BOOL>((glow_Pointer + ((glow_currentPlayerGlowIndex * someOffset) + 0x24)), m_bRenderWhenOccluded);
					procMem->WriteMemory<BOOL>((glow_Pointer + ((glow_currentPlayerGlowIndex * someOffset) + 0x25)), m_bRenderWhenUnoccluded);
					break;
			}
		}
	}
}

void Misc::AutoPistol()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		int atk = 6;
		procMem->WriteMemory(offsets->dwClientDLL + offsets->dwForceAttack, atk);
		Sleep(30);
	}
}

void Misc::NoFlash()
{
	procMem->WriteMemory(localPLayer->Player + offsets->m_flFlashMaxAlpha, 0.f);
}