
// lifegame.cpp

#include "lifegame.h"

#include "imgui_setup.h"
// #include "life_game_map.h"


void
ImGuiConfigWindow() // ImGui 配置窗口
{
    ImGui::Begin("ImGui Config");

    // 显示帧率
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    // 清屏颜色
    static ColorF color = { 0.0f, 0.0f, 0.0f, 1.0f };
    ImGui::ColorEdit4("Clear Color", color);
    Painter::Instance().clear_color = color;

    ImGui::End();
}

// void
// ImGuiLifeGameMapWindow() // ImGui 生命游戏地图窗口
// {
//     ImGui::Begin("Life Game Map");

//     LifeGameMap::Instance().On_render();
//     const Texture* texture = LifeGameMap::Instance().Get_life_game_map_texture();

//     if(texture)
//     {
//         ImGui::Image((ImTextureID)texture, ImVec2(800, 600));
//     }

//     ImGui::End();
// }

bool
Update() // 更新
{
    bool flag = true;

    EventCallback event_callback = [&flag](const Event& event) {
        if(event.type == SDL_QUIT) flag = false;
    };

    Painter::Instance().GetInput(event_callback);

    { // 主体更新
      // LifeGameMap::Instance().On_update(ImGui::GetIO().DeltaTime);
    }

    return flag;
}


void
Render() // 渲染
{
    // 渲染窗口
    ImGui::ShowDemoWindow();
    ImGuiConfigWindow();
    // ImGuiLifeGameMapWindow();
}

int
LifeGame::Run()
{
    Painter::Instance().Init("Game", IRect{ SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 1200 });

    while(Update()) Painter::Instance().Render(Render);

    Painter::Instance().Quit();

    return 0;
}
