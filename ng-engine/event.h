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
	std::vector<EventHandler<Args...>> handlers;
public:
	Event() {

	}

	void on(EventHandler<Args...> handler) {
		// assert that the handler is not already in the list
		typename std::vector<EventHandler<Args...>>::iterator it = std::find(this->handlers.begin(), this->handlers.end(), handler);
		assert(it == this->handlers.end());

		this->handlers.push_back(handler);
	}

	EventHandler<Args...> on(std::function<void(Args...)> func) {
		EventHandler handler = EventHandler(func);
		this->handlers.push_back(handler);

		return handler;
	}

	void off(EventHandler<Args...> handler) {
		typename std::vector<EventHandler<Args...>>::iterator it = std::find(this->handlers.begin(), this->handlers.end(), handler);
		assert(it != this->handlers.end()); // assert that the handler is in the list

		this->handlers.erase(it);
	}

	void off(unsigned int handlerId) {
		typename std::vector<EventHandler<Args...>>::iterator it = std::find_if(this->handlers.begin(), this->handlers.end(), [handlerId](const EventHandler<Args...> handler) {
			return handler.id() == handlerId;
			});
		assert(it != this->handlers.end()); // assert that the handler is in the list

		this->handlers.erase(it);
	}
	void emit(Args... args) {
		for (EventHandler<Args...> handler : this->handlers) {
			handler.emit(args...);
		}
	}
};

// template class Event<Collider2D*>;