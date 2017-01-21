#include "include.h"

Offsets* offsets = new Offsets();

Offsets::Offsets()
{
	dwLocalPlayer = 0xAA6834;
	m_vecOrigin = 0x134;
	oFlags = 0x100;
	dwForceJump = 0x4F5FC20;
	aEntityList = 0x4AC90F4;
	oCrosshair = 0xAA70;
	oTeamNum = 0xF0;
	oEntityLoopDist = 0x10;
	oHealth = 0xFC;
	dwForceAttack = 0x2F09228;
	dwProcessId = 0;
	hWindow = NULL;
	m_flFlashMaxAlpha = 0xA304;
	viewAngles = 0x4D0C;
}

Offsets::~Offsets()
{
}