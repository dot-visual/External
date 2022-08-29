#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include <vector>
#include <Windows.h>
#include "../Utils/Utils.h"
#include "../SDK/Offsets.h"
#include "../Utils/ProcMemory.h"

class Player {
public:
	Player(uintptr_t playerBase);
	[[nodiscard]] uintptr_t getAddress() const;

	[[nodiscard]] bool isAlive() const;
	[[nodiscard]] bool isDormant() const;
	[[nodiscard]] bool isImmune() const;
	[[nodiscard]] bool isLocalPlayer() const;
	[[nodiscard]] int getFlags() const;
	[[nodiscard]] UINT getTeam() const;
	[[nodiscard]] int getHealth() const;
	[[nodiscard]] Utils::Vector3 getEyePos() const;
	[[nodiscard]] Utils::Vector3 getPos() const;
	[[nodiscard]] Utils::Vector3 getPosition() const;

protected:
	Player() = default;
	uintptr_t playerBaseAddr{};
};

class LocalPlayer : public Player {
public:
	LocalPlayer();
	[[nodiscard]] Utils::Angle getViewAngles() const;

private:
	//LocalPlayer() = default;
};
extern LocalPlayer* localPlayer;
extern std::vector<Player*> entityList;
#endif // !PLAYER_HEADER