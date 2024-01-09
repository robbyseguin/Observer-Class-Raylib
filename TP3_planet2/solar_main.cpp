#include <iostream>
#include <chrono>

#include <Code_Utilities_Light_v2.h>
#include "Planet.h"
#include <omp.h>

using namespace std;
using namespace std::chrono;

int main()
{
    Planets planets;

    planets.init(0, "Proxima Centauri", 147, 0, 0, 30.3f);
    planets.init(1, "Wolf 359        ", -130, 0, 0, 40.3f);
    planets.init(2, "Lacaille 9352   ", 0, 150, 36, 0);
    planets.init(3, "Luyten's Star   ", -150, 0, 0, 42);
    planets.init(4, "Struve 2398 B   ", 147, 0, 0, 30.3f);
    planets.init(5, "Groombridge 34 A", -130, 0, 0, 40.3f);
    planets.init(6, "YZ Ceti         ", 0, 150, 36, 0);
    planets.init(7, "Tau Ceti        ", -150, 0, 0, 42);
    planets.init(8, "Gliese 1061     ", 147, 0, 0, 30.3f);
    planets.init(9, "Teegarden's Star", -130, 0, 0, 40.3f);
    planets.init(10, "Kapteyn's Star  ", 0, 150, 36, 0);
    planets.init(11, "Gliese 876      ", -150, 0, 0, 42);
    planets.init(12, "Gliese 229 A    ", 147, 0, 0, 30.3f);
    planets.init(13, "82 G. Eridani   ", -130, 0, 0, 40.3f);
    planets.init(14, "Gliese 581      ", 0, 150, 36, 0);
    planets.init(15, "Gliese 667 C    ", -150, 0, 0, 42);

    cout << "== Debut ==" << endl;
    planets.displayAllPositions();

    const float dt = 0.1;

    double total_time = 0;

    for (int i=0; i<5; ++i)
    {
        high_resolution_clock::time_point time_before = high_resolution_clock::now();

        // Faire bouger les planètes un grand nombre de fois

        for (int j=0; j<10000000; ++j)
        {
            planets.updateAll(dt);
        }

        high_resolution_clock::time_point time_after = high_resolution_clock::now();
        duration<double, milli> time_span = time_after - time_before;
        cout << "Temps requis : " << time_span.count() << " ms" << endl;

        total_time += time_span.count();

        cout << "== Iteration " << i << " ==" << endl;
        planets.displayAll();
    }

    cout << "== Positions finales ==" << endl;
    planets.displayAllPositions();

    cout << endl << "********************" << endl;
    cout << "Temps moyen : " << total_time / 5.0 << " ms" << endl;

    return 0;
}
