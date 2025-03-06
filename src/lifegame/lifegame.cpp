
// lifegame.cpp

#include "lifegame.h"

#include "imgui_setup.h"


bool
Update() // 更新
{
    bool flag = true;

    EventCallback event_callback = [&flag](const Event& event) {
        if(event.type == SDL_QUIT) flag = false;
    };

    Painter::Instance().GetInput(event_callback);

    { // 主体更新
    }

    return flag;
}

void
Render() // 渲染
{
    // 渲染窗口
    ImGui::ShowDemoWindow();
}


int
LifeGame::Run()
{
    Painter::Instance().Init("Game", IRect{ SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 1200 });

    while(Update()) Painter::Instance().Render(Render);

    Painter::Instance().Quit();

    return 0;
}
