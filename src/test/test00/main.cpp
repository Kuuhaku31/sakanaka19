
#include <stdio.h>

#include "testgame.h"

void
PrintGameInfo()
{
    printf("Game is initialized: %s\n", game::GetIsInitialized() ? "true" : "false");
}

int
main()
{
    printf("Hello, test00\n");

    // PrintGameInfo();
    // game::Initialize();
    // PrintGameInfo();
    // game::Play();
    // PrintGameInfo();
    // game::Shutdown();
    // PrintGameInfo();

    Singleton& singleton = Singleton::getInstance();
    singleton.show();

    return 0;
}
