#pragma once

#include <vector>

using funcType = void(*)();

class Event {
private:
	std::vector<funcType> listeners;
public:
	void on(funcType);
	void off(funcType);
	void emit();
};