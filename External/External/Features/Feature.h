#pragma once
#ifndef FEATURE_HEADER
#define FEATURE_HEADER
#include <string_view>

class Feature {
public:
	Feature() = default;
	[[nodiscard]] virtual bool isEnabled() const {
		return state;
	};
	virtual void toggle() {
		state = !state;
	}
	virtual void run() = 0;

	[[nodiscard]] virtual std::string_view getName() const = 0;
private:
	std::string_view name = "Feature";
	bool state { false };
};

#endif // !FEATURE_HEADER
