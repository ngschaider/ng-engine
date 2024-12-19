#pragma once

#include "vector2.h"

enum class AnchorPoint {
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	TopCenter,
	RightCenter,
	BottomCenter,
	LeftCenter,
	CenterCenter
};

/**
* Represents a non-rotated rectangle defined by position and size
* Commonly used for representing axis-aligned bounding boxes in collision
*/
class Rect {
private:
	/**
	* The anchor point the saved position refers to
	*/
	AnchorPoint _anchorPoint;

	/**
	* The position of the rect
	*/
	Vector2 _position;

	/**
	* The size of the rect
	*/
	Vector2 _size;

	/**
	* Returns the Y-component of the top edge
	*/
	float top() const;

	/**
	* Returns the X-component of the right edge
	*/
	float right() const;

	/**
	* Returns the Y-component of the bottom edge
	*/
	float bottom() const;

	/**
	* Returns the X-component of the left edge
	*/
	float left() const;

	/**
	* Returns the y-component of the center
	*/
	float verticalCenter() const;

	/**
	* Returns the X-component of the center
	*/
	float horizontalCenter() const;
public:
	/**
	* Constructs a new rect instance with a given position, size and anchor point.
	* The anchor point defaults to bottom left
	*/
	Rect(Vector2, Vector2);
	Rect(Vector2, Vector2, AnchorPoint);

	/**
	* Returns the anchor point of the rect
	*/
	AnchorPoint anchorPoint() const;

	/**
	* Returns the position of the rect
	*/
	Vector2 position() const;

	/**
	* Returns the size of the rect
	*/
	Vector2 size() const;

	/**
	* Returns the position of the rect's top left corner
	*/
	Vector2 topLeft();

	/**
	* Returns the position of the rect's top right corner
	*/
	Vector2 topRight();

	/**
	* Returns the position of the top edge's center
	*/
	Vector2 topCenter();

	/**
	* Returns the position of the rect's bottom left corner 
	*/
	Vector2 bottomLeft();

	/**
	* Returns the position of the rect's bottom right corner
	*/
	Vector2 bottomRight();

	/**
	* Returns the position of the right edge's center
	*/
	Vector2 rightCenter();

	/**
	* Returns the position of the bottom edge's center
	*/
	Vector2 bottomCenter();

	/**
	* Returns the position of the rect's left edge
	*/
	Vector2 leftCenter();

	/**
	* Returns the position of the rect's center
	*/
	Vector2 centerCenter();

};