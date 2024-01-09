#include <iostream>
#include <chrono>
#include <omp.h>
#include <Code_Utilities_Light_v2.h>
#include "Planet.h"


using namespace std;
using namespace std::chrono;

int main()
{
    
    Planet planets[16] = {
        {"Proxima Centauri", 147, 0, 0, 30.3f},
        {"Wolf 359        ", -130, 0, 0, 40.3f},
        {"Lacaille 9352   ", 0, 150, 36, 0},
        {"Luyten's Star   ", -150, 0, 0, 42},
        {"Struve 2398 B   ", 147, 0, 0, 30.3f},
        {"Groombridge 34 A", -130, 0, 0, 40.3f},
        {"YZ Ceti         ", 0, 150, 36, 0},
        {"Tau Ceti        ", -150, 0, 0, 42},
        {"Gliese 1061     ", 147, 0, 0, 30.3f},
        {"Teegarden's Star", -130, 0, 0, 40.3f},
        {"Kapteyn's Star  ", 0, 150, 36, 0},
        {"Gliese 876      ", -150, 0, 0, 42},
        {"Gliese 229 A    ", 147, 0, 0, 30.3f},
        {"82 G. Eridani   ", -130, 0, 0, 40.3f},
        {"Gliese 581      ", 0, 150, 36, 0},
        {"Gliese 667 C    ", -150, 0, 0, 42},
    };

    cout << "== Debut ==" << endl;
    for (Planet& planet : planets)
        planet.displayPosition();

    double total_time = 0;

    for (int loop={}; loop<5; ++loop)
    {
        high_resolution_clock::time_point time_before = high_resolution_clock::now();

        // Faire bouger chaque planète un grand nombre de fois
#pragma omp parallel for
            for (int j = 0; j < 16; ++j)
            {
                for (int i = 0; i < 10000000; ++i)
                {
                constexpr float dt = 0.1f;
                planets[j].update(dt);
            }
        }

        high_resolution_clock::time_point time_after = high_resolution_clock::now();
        duration<double, milli> time_span = time_after - time_before;
        cout << "Temps requis : " << time_span.count() << " ms" << endl;

        total_time += time_span.count();

        cout << "== Iteration " << loop << " ==" << endl;
        for (Planet& planet : planets)
            planet.display();
    }

    cout << "== Positions finales ==" << endl;
    for (Planet& planet : planets)
        planet.displayPosition();

    cout << endl << "********************" << endl;
    cout << "Temps moyen : " << total_time / 5.0 << " ms" << endl;

    return 0;
}
