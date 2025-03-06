
// runtest.cpp

#include "versions.h"

#include "game.h"
#include "lifegame.h"


int
RunSEKIBAKO(const char* resources_path)
{
    printf("RunTest: ");

    // 初始化基本
    Painter::Instance().Init("Game", IRect{ SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 1200 });
    ResourcesPool::Instance().LoadResources(resources_path);

    // 运行游戏
    Game::Instance().PlayGame();

    // 释放资源
    ResourcesPool::Instance().FreeResources();
    Painter::Instance().Quit();

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
