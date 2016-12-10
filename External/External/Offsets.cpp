#include "include.h"

Offsets* offsets = new Offsets();

Offsets::Offsets()
{
	dwLocalPlayer = 0xAA38E4;
	oFlags = 0x100;
	dwForceJump = 0x4F5CA40;
	aEntityList = 0x4AC5E94;
	oCrosshair = 0xAA70;
	oTeamNum = 0xF0;
	oEntityLoopDist = 0x10;
	oHealth = 0xFC;
	dwForceAttack = 0x2F06004;
	dwProcessId = 0;
	hWindow = NULL;
	m_flFlashMaxAlpha = 0xA304;
}

Offsets::~Offsets()
{
}