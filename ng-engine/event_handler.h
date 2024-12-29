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
	/**
	* The function associated with this event handler
	*/
	std::function<void(Args...)> func;

	/**
	* The unique id to identify the event handler
	*/
	unsigned int _id;

	/**
	* Static counter to generate new unique ids.
	*/
	static unsigned int idCounter;
public:
	/**
	* Getter for the unique id.
	*/
	inline unsigned int id() const {
		return this->_id;
	}

	/**
	* Constructs a new event handler using the provided function
	*/
	EventHandler(std::function<void(Args...)> func) : func(func) {
		this->_id = this->idCounter;
		this->idCounter++;
	}

	/**
	* Invokes the saved function
	*/
	void emit(Args... args) const {
		this->func(args...);
	}

	/**
	* Returns if two event handlers are equal.
	* Event handlers are considered equal if there ids match.
	*/
	bool operator==(EventHandler<Args...> other) {
		return this->id() == other.id();
	}
};

template<typename... Args>
unsigned int EventHandler<Args...>::idCounter = 0;