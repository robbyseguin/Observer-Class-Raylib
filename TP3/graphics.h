#pragma once
/*
    Graphics class created to remove dependency from external tool (Raylib)
*/

#include <vector>

#include "FpsCounter.h"
#include "background.h"
#include "entity.h"

using namespace GS;

class Overlay;
class Resources;

class Graphics 
{
public:
    using EntityList = std::vector<Entity*>;

	// Width and Height of the window in px
	static const int WIDTH, HEIGHT;

private:
	Resources* _resources;
	FpsCounter _fpsCounter;
	Overlay* _overlay;
	Background* _background;

    static bool initWindow();

public:
	Graphics();
    ~Graphics();

    static void startRender();
    static void endRender();
	void clearScreen() const;
	void renderOverlay() const;
	void presentRenderer(float delta);
	void renderEntities(const EntityList& entities, float delta) const;
    Background& getBackground() const;
};
