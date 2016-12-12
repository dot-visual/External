#include "include.h"

class CLocalPlayer
{
public:
	DWORD Player;

	int Team; //2 T, 3 CT
	int Flags;
	float Position[3];
	float eyePos;
	float origin[3];
	float view;
	float ViewAngles[3];
	int CrosshairID;
	DWORD enemyInCH;
	float localBones[3];
	void ReadInformation();
};
extern CLocalPlayer* localPLayer;

class CPlayer
{
public:
	DWORD Player;

	int Health;
	int Team;
	int Flags;
	float Position[3];
	float ViewAngles[3];
	bool isAlive();
	float bones[3];

private:
};
