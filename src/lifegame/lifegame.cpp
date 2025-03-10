
// lifegame.cpp

#include "lifegame.h"

#include "lifegame_map.h"

#include "imgui_windows.h"


namespace LifeGame
{


float   move_speed = 5; // 移动速度
Vector2 move_dir;       // 移动方向


} // namespace LifeGame


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


    while(SKE::IsRunning())
    {
        SKE::NewFrame(); // 新帧

        LifeGame::ProcessEvent(); // 处理事件
        LifeGameMap::OnUpdate();  // 更新地图
        LifeGameMap::OnRender();  // 渲染地图

        ImGuiConfigWindow(LifeGameMap::GetMapTex()); // 渲染窗口

        SKE::EndFrame(); // 结束帧
    }


    {
        LifeGameMap::Quit();
        SKE::Quit();
    }

    return 0;
}
