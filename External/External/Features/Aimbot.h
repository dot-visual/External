#ifndef AIMBOT_HEADER
#define AIMBOT_HEADER

#include "../SDK/Player.h"
#include "../Utils/Utils.h"
class Aimbot
{
public:
	Aimbot() = default;

	void run();
	void SetAimbot(bool state);
	[[nodiscard]] bool GetAimbot() const;

private:
	bool enabled{ false };
};

#endif