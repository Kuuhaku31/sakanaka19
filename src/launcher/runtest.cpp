
// runtest.cpp

#include "versions.h"

#include "imgui_setup.h"

int
RunTest()
{
    bool is_running = true;

    static Painter& painter = Painter::Instance();

    painter.Init("Runtest", IRect{ SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600 });

    EventCallback on_begin = [&is_running](const Event& event) {
        if(event.type == SDL_QUIT) is_running = false;
    };

    while(is_running)
    {
        painter.On_frame_begin(on_begin);

        ImGui::ShowDemoWindow();

        painter.On_frame_end();
    }

    return painter.Quit();
}
