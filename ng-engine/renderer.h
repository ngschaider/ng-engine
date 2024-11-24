#include "graphics.h"
#include "component.h"

class Renderer : public Component {
private:
public:
	virtual void render(Graphics* graphics);
};