
#include "testgame.h"

#include <stdio.h>

namespace
{
bool is_initialized = false;
}

void
game::Initialize()
{
    printf("Initializing game\n");
    is_initialized = true;
}

void
game::Play()
{
    printf("Playing game\n");
}

void
game::Shutdown()
{
    printf("Shutting down game\n");
    is_initialized = false;
}

bool
game::GetIsInitialized()
{
    return is_initialized;
}
