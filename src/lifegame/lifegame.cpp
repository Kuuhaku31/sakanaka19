
// lifegame.cpp

#include "lifegame.h"

#include "imgui_windows.h"


namespace LifeGame
{


Texture* painter_tex = nullptr; // 画板纹理
View     painter_view;          // 画板视野


} // namespace LifeGame

bool
Update() // 更新
{
    bool flag = true;

    EventCallback event_callback = [&flag](const SKE::Event& event) {
        if(event.type == SKE::Event::quit) flag = false;
    };

    SKE::ProcessEvents(event_callback);

    { // 主体更新

        SKE::SetRenderTarget(LifeGame::painter_tex, &LifeGame::painter_view); // 设置渲染目标
        SKE::RenderClear(painter_tex_color);                                  // 清屏

        SKE::DrawCircle({ 400, 300 }, 100, COLOR_BLACK, true); // 绘制圆形

        SKE::SetRenderTarget(); // 设置渲染目标
    }

    return flag;
}


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


    {
        while(Update()) SKE::Render(Render);
    }


    {
        SKE::DestroyTexture(painter_tex); // 销毋纹理
        SKE::Quit();
    }

    return 0;
}
