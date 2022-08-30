#include "Aimbot.h"
#include "../SDK/Helper.h"

Aimbot aimbot;

std::string_view Aimbot::getName() const {
	return this->name;
}

void Aimbot::run() {
	if (!isEnabled())
		return;
	if (!GetAsyncKeyState(VK_LBUTTON))
		return;

	int bestEntInd = Helper::ClosestEntIndexToPlayer();
	if (bestEntInd == INVALID_INDEX)
		return;

	auto destAngles = calcAngleTo(entityList[bestEntInd]->getEyePos());
	localPlayer->setViewAngles(destAngles);
	if (localPlayer->getEntityInCrosshair().getAddress() == entityList[bestEntInd]->getAddress()) {
		localPlayer->shoot();
	}
}

Utils::Angle Aimbot::calcAngleTo(Utils::Vector3 dst) {
	Utils::Vector3 delta = dst - localPlayer->getEyePos();
	auto hyp = delta.LengthXY();
	delta.z *= -1;

	Utils::Angle returnAngle;
	returnAngle.yaw = Utils::RadToDegrees<float>(atanf(delta.z / hyp));
	returnAngle.pitch = Utils::RadToDegrees<float>(atanf(delta.y / delta.x));

	if (delta.x < 0)
		returnAngle.pitch += 180;

	return returnAngle;
}