#pragma once
#include <Windows.h>

DWORD dwClientDLL;
DWORD dwEngineDLL;

DWORD dwLocalPlayer = 0xA9053C;
DWORD oFlags = 0x00000100;
DWORD dwForceJump = 0x4F48A94;
DWORD dwAngl = 0x4D0C;
DWORD aEntityList = 0x4AB1F54;
DWORD oCrosshair = 0x0000AA64;
DWORD oTeamNum = 0x000000F0;
DWORD oEntityLoopDist = 0x10;
DWORD oHealth = 0x000000FC;
DWORD dwForceAttack = 0x2EF1F40;
DWORD m_vecOrigin = 0x00000134;
DWORD m_vecVelocity  = 0x110;

DWORD dwProcessId = 0;
HWND hWindow = NULL;
HANDLE hProcess = NULL;