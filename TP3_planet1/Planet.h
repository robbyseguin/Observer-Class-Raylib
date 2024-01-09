#pragma once

#include <string>

class Planet
{
public:
    Planet(std::string name, float x, float y, float vx, float vy);
    void update(float dt);
    void display();
    void displayPosition();
private:
    std::string _name;
    float _x, _y;
    float _vx, _vy;
    float _ax, _ay;
};
