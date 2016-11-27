#include <Windows.h>
#include <iostream>

#include "ProcMemory.h"
#include "Offsets.h"
ProcMemory procMem;

class CLocalPlayer
{
public:
	DWORD Player;

	int Team; //2 T, 3 CT
	int Flags;
	float Position[3];
	int CrosshairID;

	void ReadInformation()
	{
		Player = procMem.ReadMemory<DWORD>(dwClientDLL + dwLocalPlayer);
		Team = procMem.ReadMemory<int>(Player + oTeamNum);
		Flags = procMem.ReadMemory<int>(Player+ oFlags);
		CrosshairID = procMem.ReadMemory<int>(Player + oCrosshair);
	}

};
extern CLocalPlayer localPLayer;