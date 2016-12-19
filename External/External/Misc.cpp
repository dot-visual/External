#include "include.h"

Misc* g_pMisc = new Misc();

CPlayer players[32];

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
				int randNum = rand()%(120-90 + 1) + 90;
				//Sleep(randNum);
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

bool Misc::GetRCS()
{
	return m_rcs;
}

void Misc::SetRCS()
{
	m_rcs = !m_rcs;
}

void Misc::SetGlow()
{
	m_glow = !m_glow;
}

bool Misc::GetGlow()
{
	return m_glow;
}

bool Misc::GetAimbot()
{
	return m_aimbot;
}

void Misc::SetAimbot()
{
	m_aimbot = !m_aimbot;
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
		if(GetAsyncKeyState(6) && enemyPlayer.isAlive() && enemyPlayer.Team != localPLayer->Team)
		{
			int vAtk = 6;
			//procMem->WriteMemory(offsets->dwClientDLL + offsets->dwForceAttack, vAtk);
			mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
			// use Sleep() here for shooting several shots with an ak for example. Not usable with pisto
			Sleep(300);
			mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
			// use Sleep() here for a 'cooldown' between shots.
			int randNum = rand()%(250-100 + 1) + 100;
			Sleep(randNum);
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
	m_rcs = false;
	m_aimbot = false;
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
		glow_Pointer = procMem->ReadMemory(offsets->dwClientDLL + 0x4FE27B4, glow_Pointer);

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

void Misc::Aimbot()
{
	if(GetAimbot())
	{
		localPLayer->ReadInformation();
		readshit();
		if(closeEnt() >= 0)
		{
			int myIndex = closeEnt();
			if(myIndex != 32)
			{
				float test[3];
				test[0] = localPLayer->Position[0] + localPLayer->origin[0];
				test[1] = localPLayer->Position[1] + localPLayer->origin[1];
				test[2] = localPLayer->Position[2] + localPLayer->origin[2];
				DWORD dwClientState = 0x5C7574;
				DWORD dwAngPtr = procMem->ReadMemory<DWORD>(offsets->dwEngineDLL + dwClientState);

				float vorher[3];
				vorher[0] = procMem->ReadMemory<float>(dwAngPtr + 0x4D0C, vorher[0]);
				vorher[1] = procMem->ReadMemory<float>(dwAngPtr + 0x4D10, vorher[1]);
				vorher[2] = procMem->ReadMemory<float>(dwAngPtr + 0x4D14, vorher[2]);

				myCalcAngle(test, players[myIndex].bones, localPLayer->ViewAngles, players[myIndex].Flags);

				if (GetAsyncKeyState(VK_RBUTTON))
				{
					RCS();
					clampAngl(localPLayer->ViewAngles);
					SmoothAngle(vorher,localPLayer->ViewAngles);
					clampAngl(localPLayer->ViewAngles);
					procMem->WriteMemory(dwAngPtr + offsets->viewAngles, localPLayer->ViewAngles);
					/*
					procMem->WriteMemory(dwAngPtr + offsets->viewAngles, (localPLayer->ViewAngles[0] - viewPunchAngle[0]) * 1.97f);
					procMem->WriteMemory(dwAngPtr + offsets->viewAngles + 0x4, (localPLayer->ViewAngles[1] - viewPunchAngle[1]));
					procMem->WriteMemory(dwAngPtr + offsets->viewAngles + 0x8, (localPLayer->ViewAngles[2] - viewPunchAngle[2])* 1.97f);
					*/
					//mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
					// use Sleep() here for shooting several shots with an ak for example. Not usable with pisto
					//mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
					// use Sleep() here for a 'cooldown' between shots.
				}
				Sleep(1);
			}
		}
	}
}
void Misc::SmoothAngle(float vecOld[3], float *vecNew)
{
	vecNew[0] = (vecNew[0] - vecOld[0]);
	vecNew[1] = (vecNew[1] - vecOld[1]);
	vecNew[2] = (vecNew[2] - vecOld[2]);
	clampAngl(vecNew);
	vecNew[0] = vecNew[0] / 30.0f + vecOld[0];
	vecNew[1] = vecNew[1] / 30.0f + vecOld[1];
	vecNew[2] = vecNew[2] / 30.0f + vecOld[2];
}

void Misc::myCalcAngle( float src[3], float *dst, float *angles, int fFlags)
{
	double delta[3] = { (src[0]-dst[0]), (src[1]-dst[1]), (src[2]-dst[2]) };
	double hyp = sqrt(delta[0]*delta[0] + delta[1]* delta[1]);
	angles[0] = (float) (asinf(delta[2]/hyp) * 57.295779513082f);
	angles[1] = (float) (atanf(delta[1]/delta[0]) * 57.295779513082f);
	angles[2] = 0.0f;

	if(delta[0] >= 0.0)
	{
		angles[1] += 180.0f;
	}
	clampAngl(angles);
}

void Misc::clampAngl(float *ang)
{
	if (ang[0] > 89.f)
		ang[0] -= 360.f;
	else if (ang[0] < -89.f)
		ang[0] += 360.f;
	if (ang[1] > 179.f)
		ang[1] -= 360.f;
	else if (ang[1] < -179.f)
		ang[1] += 360.f;

	ang[2] = 0;
}

void Misc::readshit()
{
	for (int i = 0; i < 64; i++)
	{
		players[i].Player = procMem->ReadMemory<DWORD>((offsets->dwClientDLL + offsets->aEntityList) + (i * 0x10));
		DWORD bones;
		if(!players[i].Player)
			return;

		players[i].Team = procMem->ReadMemory<int>(players[i].Player + offsets->oTeamNum);

		if (players[i].Team != localPLayer->Team)
		{
			players[i].Position[0] = procMem->ReadMemory<float>(players[i].Player + offsets->m_vecOrigin);
			players[i].Position[1] = procMem->ReadMemory<float>(players[i].Player + offsets->m_vecOrigin + 0x4);
			players[i].Position[2] = procMem->ReadMemory<float>(players[i].Player + offsets->m_vecOrigin + 0x8);
			players[i].Flags = procMem->ReadMemory<int>(players[i].Player + offsets->oFlags);
			players[i].Health = procMem->ReadMemory<int>(players[i].Player + offsets->oHealth, players[i].Health);
			bones = procMem->ReadMemory<DWORD>(players[i].Player + 0x2698);
			players[i].bones[0] = procMem->ReadMemory<float>(bones + 0x30 * 8 + 0xC);
			players[i].bones[1] = procMem->ReadMemory<float>(bones + 0x30 * 8 + 0x1C);
			players[i].bones[2] = procMem->ReadMemory<float>(bones + 0x30 * 8 + 0x2C);
			players[i].dormant = procMem->ReadMemory<int>(players[i].Player + 0x939);
		}
	}
}

float Misc::closeEnt()
{
	float fLowest = 100000, TMP;
	int iIndex;
	iIndex = -1;
	for (int i = 0; i < 64; i++)
	{
		TMP = get3d(localPLayer->Position[0],localPLayer->Position[1], localPLayer->Position[2], players[i].Position[0],players[i].Position[1], players[i].Position[2]);

		if(TMP < fLowest && (int)players[i].Health > 0 && players[i].dormant == 1)
		{
			fLowest = TMP;
			iIndex = i;
		}
	}
	return iIndex;
}

float Misc::get3d(float X, float Y, float Z, float eX, float eY, float eZ)
{
	return(sqrtf( (eX - X) * (eX - X) + (eY - Y) * (eY - Y) + (eZ - Z) * (eZ - Z)));
}

void Misc::RCS()
{
	if(GetRCS())
	{
		int ShotsFired = procMem->ReadMemory<int>(localPLayer->Player + 0xA2C0);
		if (ShotsFired > 1){
			DWORD dwClientState = 0x5C7574;
			DWORD dwAngPtr = procMem->ReadMemory<DWORD>(offsets->dwEngineDLL + dwClientState);
			float m_ViewAngle[3];
			float m_PunchAngle[3];

			m_ViewAngle[0] = procMem->ReadMemory<float>(dwAngPtr + 0x4D0C, m_ViewAngle[0]);
			m_ViewAngle[1] = procMem->ReadMemory<float>(dwAngPtr + 0x4D10, m_ViewAngle[1]);
			m_ViewAngle[2] = procMem->ReadMemory<float>(dwAngPtr + 0x4D14, m_ViewAngle[2]);

			m_PunchAngle[0] = procMem->ReadMemory<float>(localPLayer->Player + 0x301C);
			m_PunchAngle[1] = procMem->ReadMemory<float>(localPLayer->Player + 0x3020);
			m_PunchAngle[2] = procMem->ReadMemory<float>(localPLayer->Player + 0x3024);

			m_ViewAngle[0] += oldAngle[0];
			m_ViewAngle[1] += oldAngle[1];
			// Add the old "viewpunch" so we get the "center" of the screen again
			localPLayer->ViewAngles[0] = m_ViewAngle[0] - m_PunchAngle[0]*2;
			localPLayer->ViewAngles[1] = m_ViewAngle[1] - m_PunchAngle[1]*2 ;
			localPLayer->ViewAngles[2] = 0.0f;
			// remove the new "viewpunch" from the viewangles
			//SetVi*ewAngle(angle);
			procMem->WriteMemory(dwAngPtr + offsets->viewAngles, localPLayer->ViewAngles);
			oldAngle[0] = m_PunchAngle[0]*2;
			oldAngle[1] = m_PunchAngle[1]*2;
			// save the old "viewpunch"
		}else{
			oldAngle[0] = 0;
			oldAngle[1] = 0;
		}
	}
}