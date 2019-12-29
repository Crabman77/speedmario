#include <iostream>
#include "Engine.hpp"

int main()
{
    Engine engine;
    if (!engine.init("SpeedMario"))
    {
        return EXIT_FAILURE;
    }

    int ret = engine.menu();
    engine.cleanup();
    return ret;
}

