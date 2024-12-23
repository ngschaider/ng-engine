#pragma once

#include <functional>

/**
* The event handler stores a unique id and a target function. It gets added to an event and can be removed from it.
* When the event is emitted, the target function is called.
* Because of some weird C++ shit, we have to define the implementation of the methods here for template classes because
* template classes can only be instantiated when their implementation is known.
*/
template<typename... Args>
class EventHandler {
private:
	std::function<void(Args...)> func;
	unsigned int _id;
	static unsigned int idCounter;
public:
	unsigned int id() const {
		return this->_id;
	}

	EventHandler(std::function<void(Args...)> func) : func(func) {
		this->_id = this->idCounter;
		this->idCounter++;
	}

	void emit(Args... args) const {
		this->func(args...);
	}

	bool operator==(EventHandler<Args...> other) {
		return this->id() == other.id();
	}
};

template<typename... Args>
unsigned int EventHandler<Args...>::idCounter = 0;