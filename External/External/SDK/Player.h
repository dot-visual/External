#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "../Includes.h"

class Player {
	Player() = delete;
	Player(uintptr_t playerBase);

	[[nodiscard]] bool isImmune() const;
	[[nodiscard]] bool isAlive() const;
	[[nodiscard]] unsigned int getTeam() const;
	[[nodiscard]] Utils::Vector3 getPosition() const;
	[[nodiscard]] bool isDormant() const;

private:
	uintptr_t playerBaseAddr{};
};

class LocalPlayer {
public:
	static LocalPlayer& GetInstance();

	uintptr_t getAddress() const;
	int getHealth() const;
	int getFlags() const;
	Utils::Vector3 getPos() const;
	Utils::Vector3 getEyePos() const;
	Utils::Vector3 getViewAngle() const;


	// Delete copy/move so extra instances can't be created/moved.
	LocalPlayer(const LocalPlayer&) = delete;
	LocalPlayer& operator=(const LocalPlayer&) = delete;
	LocalPlayer(LocalPlayer&&) = delete;
	LocalPlayer& operator=(LocalPlayer&&) = delete;

private:
	LocalPlayer() = default;
};

#endif // !PLAYER_HEADER