#pragma once

#include <vector>
#include <functional>
#include "event_handler.h"
#include <assert.h>

/**
* An event stores a list of event handlers and can emit the event to all of them.
* Because of some weird C++ shit, we have to define the implementation of the methods here for template classes because
* template classes can only be instantiated when their implementation is known.
*/
template<typename... Args>
class Event {
private:
	/**
	* Holds all event handlers associated to the event.
	*/
	std::vector<EventHandler<Args...>> handlers;
public:
	/**
	* Attached (registers) a new event handler to the event.
	*/
	void on(EventHandler<Args...> handler) {
		// assert that the handler is not already in the list
		typename std::vector<EventHandler<Args...>>::iterator it = std::find(this->handlers.begin(), this->handlers.end(), handler);
		assert(it == this->handlers.end());

		this->handlers.push_back(handler);
	}

	/**
	* Creates a new event handler using the given function and attaches it to the event.
	* Returns the newly created event handler.
	*/
	EventHandler<Args...> on(std::function<void(Args...)> func) {
		EventHandler handler = EventHandler(func);
		this->handlers.push_back(handler);

		return handler;
	}

	/**
	* Detaches (unregisters) the given handler from the event.
	*/
	void off(EventHandler<Args...> handler) {
		// assert that the handler is in the list
		typename std::vector<EventHandler<Args...>>::iterator it = std::find(this->handlers.begin(), this->handlers.end(), handler);
		assert(it != this->handlers.end());

		this->handlers.erase(it);
	}

	/**
	* Emits the event using the given arguments. All attached (registered) event handler's functions will be invoked.
	*/
	void emit(Args... args) {
		for (EventHandler<Args...> handler : this->handlers) {
			handler.emit(args...);
		}
	}
};