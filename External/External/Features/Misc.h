#ifndef MISC_HEADER
#define MISC_HEADER

#include "Feature.h"

class Bhop : public Feature {
public:
	void run() override;
	[[nodiscard]] virtual std::string_view getName() const override;
private:
	std::string_view name = "Bhop";
};

class TriggerBot : public Feature {
public:
	void run() override;
	[[nodiscard]] virtual std::string_view getName() const override;
private:
	std::string_view name = "TriggerBot";
};

extern Bhop bhop;
extern TriggerBot triggerBot;
#endif