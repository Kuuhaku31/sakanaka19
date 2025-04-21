
// imgui_config_windows.cpp

#include "imgui_windows.h"

#include "lifegame.h"
#include "lifegame_map.h"

#include "imgui.h"


bool is_show_demo_window  = false;
bool is_show_paint_window = true;

void
ImGuiConfigWindow(bool* is_show) // ImGui 配置窗口
{
    if(is_show && !*is_show) return;

    if(is_show_demo_window) ImGui::ShowDemoWindow(&is_show_demo_window);

    ImGui::Begin("ImGui Config");

    // 显示帧率
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::Checkbox("Show Demo Window", &is_show_demo_window);                                    // 显示demo窗口
    ImGui::Checkbox("Show View Window", &LifeGame::is_show_view);                                 // 显示demo窗口

    ImGui::DragInt2("Display Size", (int32_t*)LifeGameMap::display_size, 1, 100, 2000);           // 拖动显示大小

    ImGui::DragInt2("View Offset", (int32_t*)LifeGameMap::view_offset, 1, -1000, 1000);           // 拖动视野偏移
    ImGui::DragInt2("View Display Size", (int32_t*)LifeGameMap::view_display_size, 1, 100, 2000); // 拖动视野显示大小


    ImGui::SliderFloat("Map View Zoom", &LifeGameMap::map_view_zoom, 0.1f, 10.0f); // 拖动视野缩放

    {
        // 显示速度
        ImGui::Text("Move Speed: %.2f", LifeGame::move_speed);
        ImGui::Text("Move Dir: %.2f, %.2f", LifeGame::move_dir.vx, LifeGame::move_dir.vy);

        Size size = SKE::GetTextureSize(LifeGameMap::map_tex); // 获取纹理大小

        // 显示视野大小
        ImGui::Text("View Size: %.2f, %.2f", LifeGameMap::map_view.size().vx, LifeGameMap::map_view.size().vy);
        ImGui::Text("View Unit Size: %.2f", LifeGameMap::map_view.unitSize());
        ImGui::Text("View Center: %.2f, %.2f", LifeGameMap::map_view.centerPos().vx, LifeGameMap::map_view.centerPos().vy);

        ImGui::Text("Texture Size: %d, %d", size.w, size.h);
    }


    ImGui::End();
}
