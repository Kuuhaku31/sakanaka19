
// lifegame.cpp

#include "lifegame.h"

#include "imgui_windows.h"


namespace LifeGame
{


bool is_running = true; // 是否运行

Texture* painter_tex = nullptr; // 画板纹理
View     painter_view;          // 画板视野

EventCallback event_callback = [](const SKE::Event& event) {
    if(event.type == SKE::Event::quit) is_running = false;
};


} // namespace LifeGame


void
Render() // 渲染
{
    // 渲染窗口
    ImGuiConfigWindow(LifeGame::painter_tex);
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
        SKE::CreateTexture(painter_tex, 800, 600); // 创建纹理

        painter_view.Set_view_size({ 800, 600 });
        painter_view.Set_view_center_position({ 400, 300 });
        painter_view.Set_unit_size(1.0f);
    }


    while(is_running)
    {
        SKE::NewFrame();                    // 新帧
        SKE::ProcessEvents(event_callback); // 处理事件

        SKE::SetRenderTarget(LifeGame::painter_tex, &LifeGame::painter_view); // 设置渲染目标
        SKE::RenderClear(painter_tex_color);                                  // 清屏
        SKE::DrawCircle({ 400, 300 }, 100, COLOR_BLACK, true);                // 绘制圆形

        Render(); // 渲染

        SKE::DrawBackground(); // 绘制背景
        SKE::EndFrame();       // 结束帧
    }


    {
        SKE::DestroyTexture(painter_tex); // 销毋纹理
        SKE::Quit();
    }

    return 0;
}
