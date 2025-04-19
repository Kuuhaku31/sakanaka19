
// imgui_windows.h

#pragma once

#include "sakaengine.h"


// void
// WIN_Objects_Data();

// void
// WIN_Map(bool show_win_map);

void WIN_LifeGameMap(bool show_life_game_map);


extern ColorF painter_tex_color;

void ImGuiConfigWindow(Texture* text, const View& view); // ImGui 配置窗口
