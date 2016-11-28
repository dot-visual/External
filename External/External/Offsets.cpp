#include "include.h"

Offsets* offsets = new Offsets();

Offsets::Offsets()
{
	dwLocalPlayer = 0xA9053C;
	oFlags = 0x00000100;
	dwForceJump = 0x4F48A94;
	dwAngl = 0x4D0C;
	aEntityList = 0x4AB1F54;
	oCrosshair = 0x0000AA64;
	oTeamNum = 0x000000F0;
	oEntityLoopDist = 0x10;
	oHealth = 0x000000FC;
	dwForceAttack = 0x2EF1F40;
	dwProcessId = 0;
	hWindow = NULL;
}

Offsets::~Offsets()
{
}