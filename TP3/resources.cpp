#include "resources.h"

#include <raylib.h>

#include <iostream>

// STATIC MEMBERS


const std::string Resources::RES_DIR = "../Source/TP3/res/";

Resources::Resources() {}

Resources::~Resources()
{
    // Iterate through sTextures and free them
    TextureMapList::iterator frames;
    for (frames = _textures.begin(); frames != _textures.end(); ++frames)
    {
        TextureMap::iterator frame;
        for (frame = frames->second.begin(); frame != frames->second.end(); ++frame)
        {
            frame->second = {};
        }
    }
}

bool Resources::loadTexture(Texture2D& texture, const std::string& filename)
{
    // Assumes texture is not already created

    // Imagefile -> Surface -> Texture
    // Empty surface to begin with
    Image loadedSurface;

    // Concatenate filename to resource directory
    std::string filepath = std::string(RES_DIR) + "images/" + filename;

    // Load imagefile into surface
    loadedSurface = LoadImage(filepath.c_str());
    if (loadedSurface.data == nullptr)
    {
        std::cout << "Error loading image: " << filepath << std::endl;
        return false;
    }

    // If successful, transfer the surface into the texture
    texture = LoadTextureFromImage(loadedSurface);

    // Free the temporary surface
    UnloadImage(loadedSurface);

    return true;
}

void Resources::loadResources()
{
    // TEXTURES
    loadTexture(_textures["ship1"][1], "ship1/ship1.png");
    loadTexture(_textures["ship1_piece"][1], "ship1/ship1_piece1.png");
    loadTexture(_textures["ship1_piece"][2], "ship1/ship1_piece2.png");
    loadTexture(_textures["ship1_piece"][3], "ship1/ship1_piece3.png");
    loadTexture(_textures["ship1_piece"][4], "ship1/ship1_piece4.png");

    loadTexture(_textures["ship2"][1], "ship2/ship2.png");
    loadTexture(_textures["ship2_piece"][1], "ship2/ship2_piece1.png");
    loadTexture(_textures["ship2_piece"][2], "ship2/ship2_piece2.png");
    loadTexture(_textures["ship2_piece"][3], "ship2/ship2_piece3.png");
    loadTexture(_textures["ship2_piece"][4], "ship2/ship2_piece4.png");

    loadTexture(_textures["missile1"][1], "missiles/missile1.png");
    loadTexture(_textures["missile2"][1], "missiles/missile2.png");

    loadTexture(_textures["laser1"][1], "lasers/laser1.png");
    loadTexture(_textures["laser2"][1], "lasers/laser2.png");

    loadTexture(_textures["particle"][1], "particles/particle1.png");
    loadTexture(_textures["particle"][2], "particles/particle2.png");
    loadTexture(_textures["particle"][3], "particles/particle3.png");
}

Texture2D& Resources::getTexture(const std::string& name, int frame)
{
    return _textures[name][frame];
}
