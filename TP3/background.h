#pragma once
#include "IObserver.h"
#include <string>
class Background : public obs::IObserver
{
public:
    using uint = unsigned int;

	Background(int width, int height);
	void render();
    void changeColor();
	void notify(Event evt) override;
	
private:

	int _width, _height;
    uint _r = 0, _g = 0, _b = 0;
};
