
// config.cpp

#include "config.h"

#include "imgui_setup.h"

#include "imgui_windows.h"

// static Painter& painter = Painter::Instance();
// static ResourcesManager& resources_manager = ResourcesManager::Instance();

int
Config::Init()
{
    // if(painter.Init()) return 1;
    // if(!resources_manager.LoadResources(resources_path)) return 2;

    return 0;
}

void
Config::Loop()
{
    bool is_running = true;

    std::function<void(const Event&)> event_callback = [&is_running](const Event& event) {
        if(event.type == SDL_QUIT)
        {
            is_running = false;
        }
    };

    // Main loop
    while(is_running)
    {

        Painter::Instance().On_frame_begin(event_callback);

        if(show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            ImGui::Begin("Hello, Editor!");                    // Create a window called "Hello, world!" and append into it.
            ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
            ImGui::Checkbox("Map Window", &show_another_window);
            ImGui::Checkbox("Life Game Map", &show_life_game_map);
            ImGui::Checkbox("Life Game Editor", &show_life_game_map_editor);
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // WIN_Map(show_another_window);

        // if(show_win_objects_data)
        // {
        //     WIN_Objects_Data();
        // }

        WIN_LifeGameMap(show_life_game_map);

        Painter::Instance().On_frame_end();
    }
}

int
Config::Quit()
{
    // return painter.Quit();
    return 0;
}
