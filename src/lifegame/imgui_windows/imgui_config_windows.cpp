
// imgui_config_windows.cpp

#include "imgui_windows.h"

#include "imgui.h"


bool is_show_demo_window  = false;
bool is_show_paint_window = true;

ColorF painter_tex_color = { 1.0f, 1.0f, 1.0f, 1.0f };


void
showPaintWindow(Texture* text) // 显示画板窗口
{
    if(!is_show_paint_window) return;

    ImGui::Begin("Paint Window", &is_show_paint_window);

    ImGui::Text("Paint Window");

    ImGui::ColorEdit4("Painter Texture Color", painter_tex_color);


    {
        int32_t w, h = 0;
        SKE::GetTextureSize(text, w, h); // 获取纹理大小

        ImGui::Text("Texture Size: %d, %d", w, h);
        ImGui::Image((ImTextureID)text, ImVec2(w, h));
    }


    ImGui::End();
}


void
ImGuiConfigWindow(Texture* text) // ImGui 配置窗口
{
    if(is_show_demo_window) ImGui::ShowDemoWindow(&is_show_demo_window);

    ImGui::Begin("ImGui Config");

    // 显示帧率
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    // 清屏颜色
    static ColorF color = { 0.0f, 0.0f, 0.0f, 1.0f };
    ImGui::ColorEdit4("Clear Color", color);
    SKE::GetClearColor() = color;


    ImGui::Checkbox("Show Demo Window", &is_show_demo_window);   // 显示demo窗口
    ImGui::Checkbox("Show Paint Window", &is_show_paint_window); // 显示画板窗口

    ImGui::End();

    showPaintWindow(text);
}
