
// runtest.cpp

#include "versions.h"

#include "game.h"

int
RunTest()
{
    printf("RunTest: ");

    Game::Instance().PlayGame();

    printf("OK\n");

    return 0;
}
