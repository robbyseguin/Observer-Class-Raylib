#include "ShipPart.h"

ShipPart::ShipPart(float x, float y, float vx, float vy, float rotSpeed,
                   float lifetime, int playerNum, int type, int screenW,
                   int screenH)
    : Entity(x, y, 4, 4, screenW, screenH)
    , _timeAlive{}
    , _lifetime{lifetime}
    , _vx{vx}
    , _vy{vy}
    , _angle{}
    , _rotSpeed{rotSpeed}
    , _playerNum{playerNum}
    , _type{type}
{}

void ShipPart::update(float delta)
{
    _timeAlive += delta;
    _x += _vx * delta;
    _y += _vy * delta;
    _angle += _rotSpeed * delta;

    checkBounds();
}

void ShipPart::render(Resources* resources, float delta) 
{
    const std::string texName = (_playerNum == 1) ? "ship1_piece" : "ship2_piece";
    const Texture2D& texture = resources->getTexture(texName, _type);

    const Rectangle src = {
        0.0f, 0.0f,
        static_cast<float>(texture.width),
        static_cast<float>(texture.height)
    };

    const Rectangle dst = {
        (_x - texture.width / 2.0f),
        (_y - texture.height / 2.0f),
        static_cast<float>(texture.width),
        static_cast<float>(texture.height)
    };

    const Vector2 origin = {
        static_cast<float>(texture.width) / 2,
        static_cast<float>(texture.height) / 2
    };

    const float alpha_level = (_lifetime - _timeAlive) / _lifetime * 255.0f;
    Color tint = WHITE;
    tint.a = static_cast<uchar>(alpha_level);
    DrawTexturePro(texture, src, dst, origin, _angle, tint);
}

bool ShipPart::isAlive()
{
    return _timeAlive <= _lifetime;
}

int ShipPart::getId() { return 3; }

bool ShipPart::collides() { return false; }

bool ShipPart::doesCollide(int id) { return false; }

void ShipPart::collideEntity(Entity& entity) {}