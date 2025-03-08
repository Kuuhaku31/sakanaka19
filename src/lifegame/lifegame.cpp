
// lifegame.cpp

#include "lifegame.h"

#include "imgui_windows.h"
#include "sakaengine.h"


// void
// ImGuiLifeGameMapWindow() // ImGui 生命游戏地图窗口
// {
//     ImGui::Begin("Life Game Map");

//     LifeGameMap::Instance().On_render();
//     const Texture* texture = LifeGameMap::Instance().Get_life_game_map_texture();

//     if(texture)
//     {
//         ImGui::Image((ImTextureID)texture, ImVec2(800, 600));
//     }

//     ImGui::End();
// }

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
