#include "include.h"

class CLocalPlayer
{
public:
	DWORD Player;

	int Team; //2 T, 3 CT
	int Flags;
	float Position[3];
	int CrosshairID;
	DWORD enemyInCH;

	void ReadInformation();

};
extern CLocalPlayer* localPLayer;

class CPlayer
{
public:
	DWORD Player;

	int Health;
	int Team;
	float Position[3];

	bool isAlive();

private:

};
