#ifndef MISC_HEADER
#define MISC_HEADER

class Feature {
public:
	[[nodiscard]] bool isEnabled() const;
	void toggle();
private:
	bool state { false };
};

class Bhop : public Feature {
	void run();
};

class TriggerBot : public Feature {
	void run();
};


#endif