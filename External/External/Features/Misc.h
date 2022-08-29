#ifndef MISC_HEADER
#define MISC_HEADER
#include <iostream>

class Feature {
public:
	Feature() = default;
	[[nodiscard]] bool isEnabled() const;
	void toggle();
	virtual void run();
private:
	bool state { true };
};

class Bhop : public Feature {
public:
	void run() override;
};

class TriggerBot : public Feature {
public:
	void run() override;
};

extern Bhop bhop;
extern TriggerBot triggerBot;
#endif