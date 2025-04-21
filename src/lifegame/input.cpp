
// input.cpp

#include "lifegame.h"

#include "lifegame_map.h"

#include "imgui.h"


void
LifeGame::ProcessEvent()
{
    LifeGame::move_dir.to_zero();
    if(ImGui::IsKeyDown(ImGuiKey_W))
    {
        LifeGame::move_dir.vy -= 1;
    }
    if(ImGui::IsKeyDown(ImGuiKey_S))
    {
        LifeGame::move_dir.vy += 1;
    }
    if(ImGui::IsKeyDown(ImGuiKey_A))
    {
        LifeGame::move_dir.vx -= 1;
    }
    if(ImGui::IsKeyDown(ImGuiKey_D))
    {
        LifeGame::move_dir.vx += 1;
    }
    LifeGame::move_dir.to_unit();

    // [ ] 调整大小
    if(ImGui::IsKeyDown(ImGuiKey_Q))
    {
        LifeGameMap::map_view_zoom *= 1.1f;
    }
    if(ImGui::IsKeyDown(ImGuiKey_E))
    {
        LifeGameMap::map_view_zoom *= 0.9f;
    }
}
