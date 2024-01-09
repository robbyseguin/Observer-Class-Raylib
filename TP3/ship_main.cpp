/*
vcxproj properties setup check list
-----------------------------------
- C/C++ > general > additional include folder > $(SolutionDir)include\raylib; $(SolutionDir)include\
- C/C++ > general > preprocessor > GRAPHICS_API_OPENGL_33; PLATFORM_DESKTOP
- Linker > general > additional Library Directory > $(SolutionDir)Lib\$(Platform)\$(Configuration)\
- Linker > input > additional dependencies > raylib.lib;winmm.lib
*/

#include "GameShip.h"

int main()
{
    GameShip{}.loop();
}
