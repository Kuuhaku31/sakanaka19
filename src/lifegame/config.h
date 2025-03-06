
// config.h

#pragma once

#include "base.h"

class Config : public InstanceTem<Config>
{
    friend class InstanceTem<Config>;

public: // 窗口启动参数
    const char  window_title[64] = "KH_Game_Editor";
    const bool  is_full_screen   = false;
    const IRect window_rect      = { 10, 30, 2000, 1500 };

    const char resources_path[255] = "../../resources";

    int mouse_x = 0;
    int mouse_y = 0;

public: // life game map 窗口启动参数
    const char life_game_map_window_title[64] = "Life Game Map";

    const Vector2 map_size          = { 1600, 1200 };
    const float   cell_size         = 20.0f;
    const float   camera_size_ratio = 0.95f;

public:
    bool is_mouse_left_pressed  = false;
    bool is_mouse_right_pressed = false;

    bool is_mouse_left_clicked  = false;
    bool is_mouse_right_clicked = false;

public:
    float clear_color[4] = { 0.1f, 0.1f, 0.15f, 1.00f };

    bool show_demo_window          = false;
    bool show_another_window       = false;
    bool show_win_objects_data     = false;
    bool show_life_game_map        = true;
    bool show_life_game_map_editor = true;

    bool is_space_pressed = false;
    bool is_space_clicked = false;

    bool is_num_1_pressed = false;
    bool is_num_2_pressed = false;
    bool is_num_3_pressed = false;
    bool is_num_4_pressed = false;
    bool is_num_5_pressed = false;

    bool is_T_pressed = false;
    bool is_T_clicked = false;

    bool is_P_pressed = false;
    bool is_P_clicked = false;

    bool is_left_braces_pressed  = false;
    bool is_right_braces_pressed = false;
    bool is_left_braces_clicked  = false;
    bool is_right_braces_clicked = false;

    bool is_up_arrow_pressed    = false;
    bool is_down_arrow_pressed  = false;
    bool is_left_arrow_pressed  = false;
    bool is_right_arrow_pressed = false;
    bool is_up_arrow_clicked    = false;
    bool is_down_arrow_clicked  = false;
    bool is_left_arrow_clicked  = false;
    bool is_right_arrow_clicked = false;

    bool is_minus_pressed = false;
    bool is_plus_pressed  = false;
    bool is_minus_clicked = false;
    bool is_plus_clicked  = false;

public:
    float separation = 3;   // 分离
    float cohesion   = 0.1; // 凝聚
    float rotation   = 1.5; // 旋转
    float range      = 0.8;

    float coefficient = 70.0f; // 系数，每一个单位长度对应的像素长度

public:
    int  Init();
    void Loop();
    int  Quit();

public:
    bool running = true;

private:
    bool is_initialized = false;
};
