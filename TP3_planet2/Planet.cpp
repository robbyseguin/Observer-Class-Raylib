#include <iostream>
#include <string>
#include <utility>

#include "Planet.h"

using namespace std;

// TODO: remove
static_assert(NB_PLANETS % 4 == 0, "Le nombre de planètes doit être un multiple de 4");

// Initialise une des planètes
void Planets::init(int idx, std::string name, float x, float y, float vx, float vy)
{
    _name[idx] = std::move(name);
    _x[idx] = x;
    _y[idx] = y;
    _vx[idx] = vx;
    _vy[idx] = vy;
    _ax[idx] = 0;
    _ay[idx] = 0;
}

void Planets::displayAll() const
{
    for (int i=0; i<NB_PLANETS; ++i) 
    {
        cout << "* " << _name[i] << "\tpos=(" << _x[i] << ", " << _y[i] << ")\t";
        cout << "v=(" << _vx[i] << ", " << _vy[i] << ")\t";
        cout << "acc=(" << _ax[i] << ", " << _ay[i] << ")" << endl;
    }
}

void Planets::displayAllPositions() const
{
    for (int i=0; i<NB_PLANETS; ++i)
    {
        cout << "* " << _name[i] << "\tpos=(" << _x[i] << ", " << _y[i] << ")" << endl;
    }
}

void Planets::updateAll(float dt)
{
    for (int i = 0; i < NB_PLANETS; ++i)
    {
        // TODO: Update toutes les planètes

        float a = -1.3275e9f / ((_x[i] * _x[i]) + (_y[i] * _y[i]));

        _ax[i] = _x[i] / sqrtf((_x[i] * _x[i]) + (_y[i] * _y[i])) * a;
        _ay[i] = _y[i] / sqrtf((_x[i] * _x[i]) + (_y[i] * _y[i])) * a;

        // Mise à jour de la vélocité
        _vx[i] += dt * _ax[i];
        _vy[i] += dt * _ay[i];

        // Mise à jour de la position
        _x[i] += dt * _vx[i];
        _y[i] += dt * _vy[i];
    }
}
