
// lifegame.cpp

#include "lifegame.h"

#include "imgui_windows.h"
#include "sakaengine.h"


bool
Update() // 更新
{
    bool flag = true;

    EventCallback event_callback = [&flag](const SKE::Event& event) {
        if(event.type == SKE::Event::quit) flag = false;
    };

    SKE::ProcessEvents(event_callback);

    { // 主体更新
      // LifeGameMap::Instance().On_update(ImGui::GetIO().DeltaTime);
    }

    return flag;
}


void
Render() // 渲染
{
    // 渲染窗口
    ImGuiConfigWindow();
    // ImGuiLifeGameMapWindow();
}


int
LifeGame::Run()
{
    {
        SKE::EngineInitArgs args;
        args.graph_title       = "Game";
        args.graph_layout      = { 0, 0, 1600, 1200 };
        args.graph_is_centered = true;

        SKE::Init(args);
    }


    {
        while(Update()) SKE::Render(Render);
    }


    {
        SKE::Quit();
    }

    return 0;
}
