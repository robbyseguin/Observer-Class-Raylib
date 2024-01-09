#pragma once

#include <string>
#include <map>

struct Texture;

class Resources 
{
    using Texture2D = Texture;
    using TextureMap = std::map<int, Texture2D>;
    using TextureMapList = std::map<std::string, TextureMap>;

	static const std::string RES_DIR;
    static bool loadTexture(Texture2D& texture, const std::string& filename);

public:
	Resources();
    ~Resources();

    void loadResources();
    Texture2D& getTexture(const std::string& name, int frame);

private:
    std::map<std::string, TextureMap> _textures;
};
