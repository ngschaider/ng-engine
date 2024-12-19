#include "rect.h"
#include "vector2.h"
#include <exception>

Rect::Rect(Vector2 position, Vector2 size) : Rect(position, size, AnchorPoint::BottomLeft) {
}
Rect::Rect(Vector2 position, Vector2 size, AnchorPoint anchorPoint) : _position(position), _size(size), _anchorPoint(anchorPoint) {
}

AnchorPoint Rect::anchorPoint() const {
	return this->_anchorPoint;
};
Vector2 Rect::position() const {
	return this->_position;
}
Vector2 Rect::size() const {
	return this->_size;
}

float Rect::top() const {
	if (this->anchorPoint() == AnchorPoint::TopLeft
		|| this->anchorPoint() == AnchorPoint::TopCenter
		|| this->anchorPoint() == AnchorPoint::TopRight) {
		return this->position().y();
	}
	else if (this->anchorPoint() == AnchorPoint::LeftCenter
		|| this->anchorPoint() == AnchorPoint::CenterCenter
		|| this->anchorPoint() == AnchorPoint::RightCenter) {
		return this->position().y() + this->size().y() / 2;
	}
	else if (this->anchorPoint() == AnchorPoint::BottomLeft
		|| this->anchorPoint() == AnchorPoint::BottomCenter
		|| this->anchorPoint() == AnchorPoint::BottomRight) {
		return this->position().y() + this->size().y();
	} else {
		throw new std::exception("Unexpected AnchorPoint encountered.");
	}
}

float Rect::right() const {
	if (this->anchorPoint() == AnchorPoint::TopLeft
		|| this->anchorPoint() == AnchorPoint::TopCenter
		|| this->anchorPoint() == AnchorPoint::TopRight) {
		return this->position().x() + this->size().x();
	}
	else if (this->anchorPoint() == AnchorPoint::LeftCenter
		|| this->anchorPoint() == AnchorPoint::CenterCenter
		|| this->anchorPoint() == AnchorPoint::RightCenter) {
		return this->position().x() + this->size().x() / 2;
	}
	else if (this->anchorPoint() == AnchorPoint::BottomLeft
		|| this->anchorPoint() == AnchorPoint::BottomCenter
		|| this->anchorPoint() == AnchorPoint::BottomRight) {
		return this->position().x();
	}
	else {
		throw new std::exception("Unexpected AnchorPoint encountered.");
	}
}

float Rect::bottom() const {
	if (this->anchorPoint() == AnchorPoint::TopLeft
		|| this->anchorPoint() == AnchorPoint::TopCenter
		|| this->anchorPoint() == AnchorPoint::TopRight) {
		return this->position().y() - this->size().y();
	}
	else if (this->anchorPoint() == AnchorPoint::LeftCenter
		|| this->anchorPoint() == AnchorPoint::CenterCenter
		|| this->anchorPoint() == AnchorPoint::RightCenter) {
		return this->position().y() - this->size().y() / 2;
	}
	else if (this->anchorPoint() == AnchorPoint::BottomLeft
		|| this->anchorPoint() == AnchorPoint::BottomCenter
		|| this->anchorPoint() == AnchorPoint::BottomRight) {
		return this->position().y();
	}
	else {
		throw new std::exception("Unexpected AnchorPoint encountered.");
	}
}

float Rect::left() const {
	if (this->anchorPoint() == AnchorPoint::TopLeft
		|| this->anchorPoint() == AnchorPoint::TopCenter
		|| this->anchorPoint() == AnchorPoint::TopRight) {
		return this->position().x();
	}
	else if (this->anchorPoint() == AnchorPoint::LeftCenter
		|| this->anchorPoint() == AnchorPoint::CenterCenter
		|| this->anchorPoint() == AnchorPoint::RightCenter) {
		return this->position().x() - this->size().x() / 2;
	}
	else if (this->anchorPoint() == AnchorPoint::BottomLeft
		|| this->anchorPoint() == AnchorPoint::BottomCenter
		|| this->anchorPoint() == AnchorPoint::BottomRight) {
		return this->position().x() - this->size().x();
	}
	else {
		throw new std::exception("Unexpected AnchorPoint encountered.");
	}
}

float Rect::verticalCenter() const {
	if (this->anchorPoint() == AnchorPoint::TopLeft
		|| this->anchorPoint() == AnchorPoint::TopCenter
		|| this->anchorPoint() == AnchorPoint::TopRight) {
		return this->position().y() - this->size().y() / 2;
	}
	else if (this->anchorPoint() == AnchorPoint::LeftCenter
		|| this->anchorPoint() == AnchorPoint::CenterCenter
		|| this->anchorPoint() == AnchorPoint::RightCenter) {
		return this->position().y();
	}
	else if (this->anchorPoint() == AnchorPoint::BottomLeft
		|| this->anchorPoint() == AnchorPoint::BottomCenter
		|| this->anchorPoint() == AnchorPoint::BottomRight) {
		return this->position().y() + this->size().y() / 2;
	}
	else {
		throw new std::exception("Unexpected AnchorPoint encountered.");
	}
}

float Rect::horizontalCenter() const {
	if (this->anchorPoint() == AnchorPoint::TopLeft
		|| this->anchorPoint() == AnchorPoint::TopCenter
		|| this->anchorPoint() == AnchorPoint::TopRight) {
		return this->position().x() + this->size().x() / 2;
	}
	else if (this->anchorPoint() == AnchorPoint::LeftCenter
		|| this->anchorPoint() == AnchorPoint::CenterCenter
		|| this->anchorPoint() == AnchorPoint::RightCenter) {
		return this->position().x();
	}
	else if (this->anchorPoint() == AnchorPoint::BottomLeft
		|| this->anchorPoint() == AnchorPoint::BottomCenter
		|| this->anchorPoint() == AnchorPoint::BottomRight) {
		return this->position().x() - this->size().x();
	}
	else {
		throw new std::exception("Unexpected AnchorPoint encountered.");
	}
}

Vector2 Rect::topLeft() {
	return Vector2(this->left(), this->top());
}

Vector2 Rect::topRight() {
	return Vector2(this->right(), this->top());
}

Vector2 Rect::topCenter() {
	return Vector2(this->horizontalCenter(), this->top());
}

Vector2 Rect::bottomCenter() {
	return Vector2(this->horizontalCenter(), this->bottom());
}

Vector2 Rect::rightCenter() {
	return Vector2(this->right(), this->verticalCenter());
}

Vector2 Rect::centerCenter() {
	return Vector2(this->horizontalCenter(), this->verticalCenter());
}

Vector2 Rect::leftCenter() {
	return Vector2(this->left(), this->verticalCenter());
}

Vector2 Rect::bottomLeft() {
	return Vector2(this->left(), this->bottom());
}

Vector2 Rect::bottomRight() {
	return Vector2(this->right(), this->bottom());
}