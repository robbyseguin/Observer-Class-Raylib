#include "graphics.h"

#include <iostream>
#include "raylib.h"

#include "resources.h"
#include "overlay.h"
#include "player.h"

using namespace std;

// STATIC MEMBERS

const int Graphics::WIDTH = 800, Graphics::HEIGHT = 800;

Graphics::Graphics() 
{
    initWindow();
    _resources = new Resources();
    _resources->loadResources();
    _background = new Background{ WIDTH, HEIGHT };
    _overlay = new Overlay(WIDTH, HEIGHT, *_resources);
    _fpsCounter = FpsCounter();
}

Graphics::~Graphics() 
{
    delete _resources;
    delete _overlay;

    CloseWindow();
}

void Graphics::startRender() { BeginDrawing(); }
void Graphics::endRender() { EndDrawing(); }

bool Graphics::initWindow() 
{
    // Create SDL Window
    InitWindow( WIDTH, HEIGHT, "Raylib Game");
    SetTargetFPS(60);

    return true;
}

// PUBLIC FUNCTIONS
void Graphics::clearScreen() const
{
    _background->render();
};

void Graphics::renderOverlay() const
{
    _overlay->renderFps(lround(_fpsCounter.getFps()));
}

void Graphics::presentRenderer(float delta) 
{
    _fpsCounter.count(delta);
}

void Graphics::renderEntities(const EntityList& entities, float delta) const
{
    for (Entity* entity : entities)
        entity->render(_resources, delta);
}

Background& Graphics::getBackground() const
{
    return *_background;
}