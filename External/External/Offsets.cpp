#include "include.h"

Offsets* offsets = new Offsets();

Offsets::Offsets()
{
	dwLocalPlayer = 0xA9E8E4;
	oFlags = 0x100;
	dwForceJump = 0x4F5782C;
	aEntityList = 0x4AC0CA4;
	oCrosshair = 0xAA70;
	oTeamNum = 0xF0;
	oEntityLoopDist = 0x10;
	oHealth = 0xFC;
	dwForceAttack = 0x2F00DF4;
	dwProcessId = 0;
	hWindow = NULL;
}

Offsets::~Offsets()
{
}