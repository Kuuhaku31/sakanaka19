
// imgui_windows.cpp

#include "imgui_windows.h"

#include "bird_manager.h"
#include "config.h"
#include "life_game_map.h"


#include "imgui.h"

// void
// WIN_Objects_Data()
// {
//     static const Map& map = Map::Instance();

//     static const Map::MapBirds& object_list = map.Get_object_list();

//     ImGui::Begin("Objects Data");

//     ImGui::Text("Object number: %d", object_list.size());

//     for(const Bird& obj : object_list)
//     {
//         ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0xff, 0, 0, 255)); // 红色
//         ImGui::Text("Object %d:", obj.Get_id());
//         ImGui::PopStyleColor();
//         ImGui::Text("  Tile idx: %d", obj.Get_tile_idx());
//         ImGui::Text("  Position: (%.2f, %.2f)", obj.Get_position().vx, obj.Get_position().vy);
//         ImGui::Text("  Velocity: (%.2f, %.2f)", obj.Get_velocity().vx, obj.Get_velocity().vy);
//         ImGui::Text("  View range: %.2f", obj.Get_view_range());
//         ImGui::Text("  View Objects: ");
//         for(const Bird* view_obj : obj.Get_view_birds())
//         {
//             ImGui::SameLine();
//             ImGui::Text("%d, ", view_obj->Get_id());
//         }
//     }

//     ImGui::End();
// }

// void
// WIN_Map(bool show_win_map)
// {
//     static Config&  config  = Config::Instance();
//     static Painter& painter = Painter::Instance();

//     static Map& map = Map::Instance();

//     if(!show_win_map) return;

//     Texture* map_tex = map.On_render();

//     // 获取纹理的宽高
//     int map_tex_wide = 0;
//     int map_tex_high = 0;
//     SDL_QueryTexture(map_tex, nullptr, nullptr, &map_tex_wide, &map_tex_high);

//     ImVec2 window_size = ImVec2(map_tex_wide + 270, map_tex_high + ImGui::GetFrameHeight());

//     ImGui::SetNextWindowSize(window_size);
//     ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
//     ImGui::Begin("Map Window", nullptr, flags);

//     ImVec2  window_pos    = ImGui::GetWindowPos();
//     ImVec2  map_pos       = { window_pos.x, window_pos.y + ImGui::GetFrameHeight() };
//     ImVec2  mouse_pos     = ImVec2(config.get_mouse_x(), config.get_mouse_y());
//     ImVec2  mouse_map_pos = { mouse_pos.x - map_pos.x, mouse_pos.y - map_pos.y };
//     Vector2 obj_pos       = { mouse_map_pos.x / config.coefficient, mouse_map_pos.y / config.coefficient };

//     map.mouse_map_x = mouse_map_pos.x;
//     map.mouse_map_y = mouse_map_pos.y;

//     int obj_idx = -1;
//     if(config.is_num_1_pressed) obj_idx = 0;
//     if(config.is_num_2_pressed) obj_idx = 1;
//     if(config.is_num_3_pressed) obj_idx = 2;
//     if(config.is_num_4_pressed) obj_idx = 3;
//     if(config.is_num_5_pressed) obj_idx = 4;
//     map.Set_obj_position(obj_idx, obj_pos);

//     // 根据鼠标位置更新地图，返回地图纹理
//     map.On_update(painter.Get_delta_time());

//     int text_offset = map_tex_wide + 10;

//     ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // 设置窗口内边距
//     ImGui::SetCursorPos(ImVec2(0, ImGui::GetFrameHeight()));        // 设置光标位置

//     ImGui::Image((ImTextureID)map_tex, ImVec2(map_tex_wide, map_tex_high));

//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetFrameHeight() + 9)); // 设置光标位置
//     ImGui::Text("Window Pos: (%.2f, %.2f)", window_pos.x, window_pos.y);
//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetCursorPosY())); // 设置光标位置
//     ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / painter.Get_frame_rate(), painter.Get_frame_rate());
//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetCursorPosY())); // 设置光标位置
//     ImGui::Text("Map Wide: %d, Map High: %d", map_tex_wide, map_tex_high);
//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetCursorPosY())); // 设置光标位置
//     ImGui::Text("Mouse Map Pos: (%.2f, %.2f)", mouse_map_pos.x, mouse_map_pos.y);
//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetCursorPosY()));

//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetCursorPosY()));
//     ImGui::Checkbox("Show Objects Data", &config.show_win_objects_data);

//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetCursorPosY()));
//     ImGui::Text("fen");
//     ImGui::SameLine();
//     ImGui::InputFloat4("separation", &config.separation);

//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetCursorPosY()));
//     ImGui::Text("ju");
//     ImGui::SameLine();
//     ImGui::InputFloat4("cohesion", &config.cohesion);

//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetCursorPosY()));
//     ImGui::Text("zuan");
//     ImGui::SameLine();
//     ImGui::InputFloat4("rotation", &config.rotation);

//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetCursorPosY()));
//     ImGui::Text("range");
//     ImGui::SameLine();
//     ImGui::InputFloat4("range", &config.range);

//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetCursorPosY()));
//     ImGui::Text("coefficient");
//     ImGui::SameLine();
//     ImGui::InputFloat4("coefficient", &config.coefficient);

//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetCursorPosY()));
//     ImGui::Checkbox("Show Bird View", &map.is_show_bird_view);

//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetCursorPosY()));
//     ImGui::Checkbox("Show Bird Line", &map.is_show_bird_line);

//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetCursorPosY()));
//     ImGui::Checkbox("Show Bird Tile", &map.is_show_bird_tile);

//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetCursorPosY()));
//     ImGui::Checkbox("Is Birds Goto Target", &map.is_birds_goto_target);

//     // 滑动条，设置coefficient
//     ImGui::SetCursorPos(ImVec2(text_offset, ImGui::GetCursorPosY()));
//     ImGui::SliderFloat("coefficient", &config.coefficient, 10.0f, 100.0f);

//     ImGui::PopStyleVar(); // 恢复窗口内边距
//     ImGui::End();
// }

void
WIN_LifeGameMap(bool show_life_game_map)
{
    static Config&        config            = Config::Instance();
    static const Painter& painter           = Painter::Instance();
    static LifeGameMap&   life_game_map     = LifeGameMap::Instance();
    static BirdManager&   bird_manager      = BirdManager::Instance();
    static const Texture* life_game_map_tex = nullptr;

    static Point window_pos;
    static Point mouse;
    static Point mouse_win;
    static Point tex_size;

    if(!show_life_game_map) return;

    life_game_map.On_update(ImGui::GetIO().DeltaTime);
    life_game_map.On_render();

    life_game_map_tex = life_game_map.Get_life_game_map_texture();

    // 获取纹理的宽高
    tex_size = life_game_map.Get_map_size();

    // 开启窗口
    ImGui::SetNextWindowSize(ImVec2(tex_size.px, tex_size.py + ImGui::GetFrameHeight()));
    ImGui::Begin("Life Game Map Window", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    // 获取窗口、鼠标、鼠标在窗口中的位置
    window_pos.px = ImGui::GetWindowPos().x;
    window_pos.py = ImGui::GetWindowPos().y + ImGui::GetFrameHeight();
    mouse.px      = config.mouse_x;
    mouse.py      = config.mouse_y;
    mouse_win     = mouse - window_pos;

    life_game_map.mouse_win = mouse_win;

    // 正文
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // 设置窗口内边距
    ImGui::SetCursorPos(ImVec2(0, ImGui::GetFrameHeight()));        // 设置光标位置
    ImGui::Image((ImTextureID)life_game_map_tex, ImVec2(tex_size.px, tex_size.py));
    ImGui::PopStyleVar(); // 恢复窗口内边距

    ImGui::End();

    // Editor
    if(!config.show_life_game_map_editor) return;

    ImGui::Begin("Editor", &config.show_life_game_map_editor);
    ImGui::Text("Mouse  Pos: (%d, %d)", mouse.px, mouse.py);
    ImGui::Text("Mouse Win Pos: (%d, %d)", mouse_win.px, mouse_win.py);
    Vector2 center_pos = life_game_map.Get_view_center_position();

    Vector2 map_size  = (Vector2)life_game_map.Get_map_size();
    float   cell_size = life_game_map.Get_cell_size();

    // 输入
    ImGui::SliderFloat2("View Center", (float*)center_pos, -50, 50);
    ImGui::SliderFloat2("Map Wide High", (float*)map_size, 0, 2000);
    ImGui::InputFloat("Cell Size", &cell_size, 0.0f, 0.0f, "%.8f");

    ImGui::Checkbox("Show Bird", &bird_manager.is_show_bird);
    ImGui::Checkbox("Show Bird View", &bird_manager.is_show_bird_view);
    ImGui::Checkbox("Show Bird Line", &bird_manager.is_show_bird_line);
    ImGui::Checkbox("Is Birds Goto Target", &bird_manager.is_birds_goto_target);

    ImGui::DragFloat("Separation", &config.separation, 0.01f, 0.0f, 5.0f); // 分离
    ImGui::DragFloat("Cohesion", &config.cohesion, 0.01f, 0.0f, 5.0f);     // 凝聚
    ImGui::DragFloat("Rotation", &config.rotation, 0.01f, 0.0f, 5.0f);     // 旋转

    Vector2 mouse_map_pos = life_game_map.Get_mouse_map_pos();
    ImGui::Text("Mouse Map Pos: (%.2f, %.2f)", mouse_map_pos.vx, mouse_map_pos.vy);

    life_game_map.Set_view_center_position(center_pos);
    life_game_map.Set_map_size(map_size);
    life_game_map.Set_cell_size(cell_size);

    ImGui::End();
}