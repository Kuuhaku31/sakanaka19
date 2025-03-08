
// runtest.cpp

#include "versions.h"

#include "lifegame.h"
#include "sekibako.h"

#include <stdio.h>


int
RunSEKIBAKO(const char* resources_path)
{
    printf("RunTest: ");

    InitArgs args = {
        .graph_title    = "SEKIBAKO",
        .graph_rect     = { 30, 40, 1600, 1200 },
        .resources_path = resources_path,
    };

    SEKIBAKO::Instance().Run(args);

    printf("OK\n");

    return 0;
}


//==============================================================================


int
RunLifeGame()
{
    printf("RunLifeGame: ");

    LifeGame::Instance().Run();

    printf("OK\n");

    return 0;
}
