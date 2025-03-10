
// input.cpp

#include "lifegame.h"

#include "imgui.h"


void
LifeGame::ProcessEvent()
{
    if(ImGui::IsKeyDown(ImGuiKey_A))
    {
        printf("A\n");
    }
}
