#ifndef AIMBOT_HEADER
#define AIMBOT_HEADER

#include "../SDK/Player.h"
#include "../Utils/Utils.h"
#include "../Features/Feature.h"

class Aimbot : public Feature
{
public:
	Aimbot() = default;
	void run() override;
	[[nodiscard]] std::string_view getName() const override;
private:
	std::string_view name = "Aimbot";
	[[nodiscard]] Utils::Angle calcAngleTo(Utils::Vector3 dst);
};

extern Aimbot aimbot;
#endif