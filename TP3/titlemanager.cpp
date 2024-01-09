#include "titlemanager.h"

#include <string>
#include <sstream>

#include <raylib.h>
#include <Code_Utilities_Light_v2.h>

using namespace std;

TitleManager::TitleManager() {}

void TitleManager::updateTitle()
{
    ostringstream title;
    // os << "dec: " << 15 << " hex: " << std::hex << 15 << endl;
    // cout << os.str() << endl;
 
    // string title;
    title << "Raylib Game || ";
    title << _nbMissiles;
    title << " missile(s) launched || ";
    title << _nbDeaths;
    title << " ship(s) destroyed";
    
    if (BdB::randInt(2))
        SetWindowTitle(title.str().c_str());
}

void TitleManager::incrementNbMissiles()
{
    ++_nbMissiles;
}

void TitleManager::incrementNbDeaths()
{
    ++_nbDeaths;
}
void TitleManager::notify(Event evt)
{
    if (evt == Event::MISSILE_SHOT)
    {
        cout << "Update Missile counter" << endl;
        incrementNbMissiles();
    }
    if ( evt == Event::SHIP_DESTROYED)
    {
        cout << "Update Death counter" << endl;
        incrementNbDeaths();
    }
}
