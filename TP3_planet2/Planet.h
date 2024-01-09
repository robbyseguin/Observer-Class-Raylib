#pragma once

#include <string>

static constexpr int NB_PLANETS = 16;

class Planets
{
public:
    Planets() = default;

    // Initialise une des planètes
    void init(int idx, std::string name, float x, float y, float vx, float vy);

    // Update toutes les planètes
    void updateAll(float dt);

    // Affiche toutes les planètes
    void displayAll() const;
    void displayAllPositions() const;

private:
    std::string _name[NB_PLANETS];
    alignas(16) float _x[NB_PLANETS]{};
    alignas(16) float _y[NB_PLANETS]{};
    alignas(16) float _vx[NB_PLANETS]{};
    alignas(16) float _vy[NB_PLANETS]{};
    alignas(16) float _ax[NB_PLANETS]{};
    alignas(16) float _ay[NB_PLANETS]{};
};
