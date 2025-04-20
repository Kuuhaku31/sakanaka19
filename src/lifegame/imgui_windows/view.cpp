
#include "imgui_windows.h"

#include "imgui.h"
#include "lifegame_map.h"

void
ImGuiViewWindow(bool* is_show) // ImGui 视图窗口
{
    if(is_show && !*is_show) return;

    ImGui::Begin("View Window", is_show);

    int32_t w, h = 0;
    SKE::GetTextureSize(LifeGameMap::map_tex, w, h); // 获取纹理大小
    ImGui::Image((ImTextureID)LifeGameMap::map_tex, ImVec2(w, h));

    ImGui::End();
}
