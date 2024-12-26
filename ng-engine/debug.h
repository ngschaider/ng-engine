#pragma once

#include "vector3.h"
#include "renderer.h"
#include "color.h"
#include "rect.h"

typedef struct {
	Vector3 start;
	Vector3 end;
	Color color;
	float width;
} Line;

typedef struct {
	Vector3 position;
	float radius;
} Circle;

typedef struct {
	Vector3 position;
	std::string text;
	Color color;
} Text;

class Debug : public Renderer {
private:
	std::vector<Line> lines;
	std::vector<Rect> rectangles;
	std::vector<Circle> circles;
	std::vector<Text> texts;
public:
	static Debug* instance;
	Debug();
	void line(Vector3 start, Vector3 end, Color color = Color::black(), float width = 1.0f);
	void line(Vector2 start, Vector2 end, Color color = Color::black(), float width = 1.0f);
	void rect(Rect rect);
	void circle(Vector3 center, float radius);
	void text(Vector3 position, std::string text, Color color = Color::black());

	void earlyUpdate() override;
	void render();
};
