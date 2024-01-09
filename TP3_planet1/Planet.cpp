#include <iostream>
#include <string>
#include <utility>

#include "Planet.h"

using namespace std;

Planet::Planet(string name, float x, float y, float vx, float vy)
    : _name(std::move(name))
    , _x(x)
    , _y(y)
    , _vx(vx)
    , _vy(vy)
    , _ax(0)
    , _ay(0)
{}

void Planet::display()
{
    cout << "* " << _name << "\tpos=(" << _x << ", " << _y << ")\t";
    cout << "v=(" << _vx << ", " << _vy << ")\t";
    cout << "acc=(" << _ax << ", " << _ay << ")" << endl;
}

void Planet::displayPosition()
{
    cout << "* " << _name << "\tpos=(" << _x << ", " << _y << ")" << endl;
}

void Planet::update(float dt)
{
    // Mise à jour de l'accélération en direction du soleil
    float a = -1.3275e9f / ((_x * _x) + (_y * _y));

    _ax = _x / sqrtf((_x * _x) + (_y * _y)) * a;
    _ay = _y / sqrtf((_x * _x) + (_y * _y)) * a;

    // Mise à jour de la vélocité
    _vx += dt * _ax;
    _vy += dt * _ay;

    // Mise à jour de la position
    _x += dt * _vx;
    _y += dt * _vy;
}
