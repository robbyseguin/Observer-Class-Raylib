#pragma once
#include "IObserver.h"
#include <string>

class TitleManager : public obs::IObserver
{
public:

    TitleManager();
    
    void updateTitle();
    void incrementNbMissiles();
    void incrementNbDeaths();
    void notify(Event evt)override;
    
private:
    int _nbMissiles = 0;
    int _nbDeaths = 0;
};
