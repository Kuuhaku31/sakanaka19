
// lifegame.cpp

#include "lifegame.h"

#include "imgui_windows.h"


Texture* painter_tex = nullptr; // 画板纹理


bool
Update() // 更新
{
    bool flag = true;

    EventCallback event_callback = [&flag](const SKE::Event& event) {
        if(event.type == SKE::Event::quit) flag = false;
    };

    SKE::ProcessEvents(event_callback);

    { // 主体更新

        SKE::SetRenderTarget(painter_tex);   // 设置渲染目标
        SKE::RenderClear(painter_tex_color); // 清屏
        SKE::SetRenderTarget();              // 设置渲染目标
    }

    return flag;
}


void
Render() // 渲染
{
    // 渲染窗口
    ImGuiConfigWindow(painter_tex);
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
