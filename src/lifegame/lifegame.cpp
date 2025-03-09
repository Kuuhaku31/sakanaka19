
// lifegame.cpp

#include "lifegame.h"

#include "lifegame_map.h"

#include "imgui_windows.h"


int
LifeGame::Run()
{
    {
        SKE::EngineInitArgs args;
        args.graph_title       = "Game";
        args.graph_layout      = { 0, 0, 1600, 1200 };
        args.graph_is_centered = true;

        SKE::Init(args);
        LifeGameMap::Init();
    }


    while(SKE::is_running)
    {
        SKE::NewFrame(); // 新帧


        LifeGameMap::OnUpdate(0.0f); // 更新地图
        LifeGameMap::OnRender();     // 渲染地图

        // 渲染窗口
        ImGuiConfigWindow(LifeGameMap::GetMapTex());

        SKE::DrawBackground(); // 绘制背景
        SKE::EndFrame();       // 结束帧
    }


    {
        LifeGameMap::Quit();
        SKE::Quit();
    }

    return 0;
}
