#pragma once

#include <vector>

class Event {
private:
	std::vector<void()> listeners;
public:
	void on(void*);
	void off(void*);
	void emit();
};