#include "include.h"

class CLocalPlayer
{
public:
	DWORD Player;

	int Team; //2 T, 3 CT
	int Flags;
	float Position[3];
	int CrosshairID;

	void ReadInformation();

};
extern CLocalPlayer* localPLayer;