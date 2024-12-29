#pragma once

#include "vector3.h"
#include "renderer.h"
#include "color.h"
#include "rect.h"

/**
* Holds alls values needed to specify a draw call for a line used for debugging.
*/
typedef struct {
	Vector3 start;
	Vector3 end;
	Color color;
	float width;
} Line;

/**
* Holds alls values needed to specify a draw call for a circle used for debugging.
*/
typedef struct {
	Vector3 position;
	float radius;
} Circle;


/**
* Holds alls values needed to specify a draw call for a text used for debugging.
*/
typedef struct {
	Vector3 position;
	std::string text;
	Color color;
} Text;

class Debug : public Renderer {
private:
	/**
	* Holds all lines that need to be rendered on the next render cycle.
	*/
	std::vector<Line> lines;

	/**
	* Holds all rectangles that need to be rendered on the next render cycle.
	*/
	std::vector<Rect> rectangles;

	/**
	* Holds all circles that need to be rendered on the next render cycle.
	*/
	std::vector<Circle> circles;

	/**
	* Holds all texts that need to be rendered on the next render cycle.
	*/
	std::vector<Text> texts;
public:
	static Debug* instance;
	Debug();

	/**
	* Saves a line to be rendered on the next render cycle.
	*/
	void line(Vector3 start, Vector3 end, Color color = Color::black(), float width = 1.0f);
	
	/**
	* Saves a line to be rendered on the next render cycle. 
	* The Z-components of the positions are assumed to be zero.
	*/
	void line(Vector2 start, Vector2 end, Color color = Color::black(), float width = 1.0f);

	/**
	* Saves a rectangle to be rendered on the next render cycle.
	*/
	void rect(Rect rect);

	/**
	* Saves a circle to be rendered on the next render cycle.
	*/
	void circle(Vector3 center, float radius);

	/**
	* Saves a text to be rendered on the next render cycle.
	*/
	void text(Vector3 position, std::string text, Color color = Color::black());

	/**
	* The early update signal of the engine.
	* Clears the stored debug information to be ready to collect new information in the update cycle.
	*/
	void earlyUpdate() override;

	/**
	* Renders the stored debug information.
	*/
	void render() override;
};
