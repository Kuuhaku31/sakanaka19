
// sekibako.cpp

#include "sekibako.h"

#include "game.h"
#include "imgui_setup.h"


int
SEKIBAKO::Run(InitArgs& args)
{
    init(args);
    loop();
    quit();
    return 0;
}

void
SEKIBAKO::init(InitArgs& args)
{
    Painter::Instance().Init(args.graph_title, args.graph_rect);
    ResourcesPool::Instance().LoadResources(args.resources_path);
}

void
SEKIBAKO::loop()
{
    // 运行游戏
    Game::Instance().PlayGame();
}

void
SEKIBAKO::quit()
{
    ResourcesPool::Instance().FreeResources();
    Painter::Instance().Quit();
}
