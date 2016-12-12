#ifndef OFFSETS_HEADER
#define OFFSETS_HEADER
#include "include.h"

class Offsets
{
public:
	Offsets();
	~Offsets();

	DWORD dwClientDLL;
	DWORD dwEngineDLL;

	DWORD dwLocalPlayer;
	DWORD m_vecOrigin;
	DWORD oFlags;
	DWORD dwForceJump;
	DWORD dwAngl;
	DWORD aEntityList;
	DWORD oCrosshair;
	DWORD oTeamNum;
	DWORD oEntityLoopDist;
	DWORD oHealth;
	DWORD dwForceAttack;
	DWORD m_flFlashMaxAlpha;
	DWORD viewAngles;

	DWORD dwProcessId;
	HWND hWindow;
private:
};
extern Offsets* offsets;


#endif