// test01

#include "imgui.h"
#include "sakaengine.h"

#include <stdio.h>

int
main()
{
    printf("Hello World\n");
    {
        SKE::EngineInitArgs args;
        args.graph_title       = "Game";
        args.graph_layout      = { 0, 0, 1600, 1200 };
        args.graph_is_centered = true;

        SKE::Init(args);
    }

    while(SKE::IsRunning())
    {
        SKE::NewFrame();         // 新帧

        ImGui::ShowDemoWindow(); // 显示演示窗口

        SKE::EndFrame();         // 结束帧
    }


    SKE::Quit();
    return 0;
}