#include "include.h"

Offsets* offsets = new Offsets();

Offsets::Offsets()
{
	dwLocalPlayer = 0x00AA5834;
	m_vecOrigin = 0x134;
	oFlags = 0x100;
	dwForceJump = 0x4F5EB58;
	aEntityList = 0x04AC8014;
	oCrosshair = 0xAA70;
	oTeamNum = 0xF0;
	oEntityLoopDist = 0x10;
	oHealth = 0xFC;
	dwForceAttack = 0x2F09364;
	dwProcessId = 0;
	hWindow = NULL;
	m_flFlashMaxAlpha = 0xA304;
	viewAngles = 0x4D0C;
}

Offsets::~Offsets()
{
}