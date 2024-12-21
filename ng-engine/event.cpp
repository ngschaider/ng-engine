#include "event.h"
#include "assert.h"

void Event::on(funcType callback) {
	this->listeners.push_back(callback);
}

void Event::off(funcType callback) {
	std::vector<funcType>::iterator it = std::find(this->listeners.begin(), this->listeners.end(), callback);
	assert(it != this->listeners.end());

	this->listeners.erase(it);
}

void Event::emit() {
	for (funcType callback : this->listeners) {
		callback();
	}
}