
// runtest.cpp

#include "versions.h"

#include "imgui_setup.h"

int
RunTest()
{
    bool is_running = true;

    static Painter& painter = Painter::Instance();

    painter.Init("Runtest", IRect{ 0, 0, 800, 600 });

    painter.On_frame_begin([&is_running](const Event& event) {
        if(event.type == SDL_QUIT) is_running = false;
    });

    while(is_running)
    {
        painter.On_frame_begin();

        ImGui::ShowDemoWindow();

        painter.On_frame_end();
    }

    return painter.Quit();
}
