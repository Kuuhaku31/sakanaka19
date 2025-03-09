
// input.cpp

#include "lifegame.h"

#include "imgui.h"


void
LifeGame::ProcessEvents()
{
    ImGuiIO& io = ImGui::GetIO();

    if(io.KeysData[SDL_SCANCODE_ESCAPE])
    {
        LifeGame::is_running = false;
    }
}
