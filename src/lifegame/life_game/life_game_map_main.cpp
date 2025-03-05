
// life_game_map_main.cpp

// #include "life_game_map.h"

#include "config.h"

#include "bird_manager.h"
#include "life_game_map.h"
#include "planet_manager.h"

#include "draw_planet.h"

static Painter& painter = Painter::Instance();

static Config& config = Config::Instance();

void
LifeGameMap::on_update_map_mouse()
{
    // 更新鼠标
    if(mouse_win < Point(0, 0) || mouse_win > map_size)
    {
        is_mouse_in_map = false;
    }
    else
    {
        is_mouse_in_map = true;

        // 更新鼠标在地图中的位置
        // mouse_map_pos = (Vector2)mouse_win / cell_size + view_left_top_position;
        mouse_map_pos = (Vector2)mouse_win / life_map_view.Get_unit_size() + life_map_view.Get_view_left_top_position();

        // 更新选中的细胞索引，注意当坐标小于0时，向上取整
        selected_cell_idx.px = mouse_map_pos.vx >= 0 ? (int)mouse_map_pos.vx : (int)mouse_map_pos.vx - 1;
        selected_cell_idx.py = mouse_map_pos.vy >= 0 ? (int)mouse_map_pos.vy : (int)mouse_map_pos.vy - 1;

        // 更新选中的细胞位置
        selected_cell_map_pos = (Vector2)selected_cell_idx;
    }
}

void
LifeGameMap::on_update_map_cells()
{
    map_cells.clear();
}

void
LifeGameMap::on_render_map_cells() const
{
    // 绘制细胞
    for(const Cell& cell : map_cells)
    {
        uint8_t alpha = -2550 / (cell.count + 10) + 255;

        painter.DrawRect(
            cell.idx.px,
            cell.idx.py,
            1,
            1,
            { 0x11, 0x11, 0x99, alpha },
            false

        );
    }
}

void
LifeGameMap::on_render_map_mouse() const
{
    // 如果鼠标在地图内
    if(is_mouse_in_map)
    {
        painter.DrawRect(
            selected_cell_idx.px,
            selected_cell_idx.py,
            1,
            1,
            { 0xff, 0x0, 0x0, 0xff },
            true

        );
    }
}

void
LifeGameMap::On_update(float delta_time)
{
    static BirdManager&   bird_manager   = BirdManager::Instance();
    static PlanetManager& planet_manager = PlanetManager::Instance();

    float cell_size = life_map_view.Get_unit_size();

    Vector2 view_center_position = life_map_view.Get_view_center_position();
    Vector2 view_size_half       = life_map_view.Get_view_size_half();

    if(config.is_P_clicked)
    {
        Set_view_center_position(mouse_map_pos);
    }

    if(config.is_right_braces_pressed)
    {
        Set_cell_size(cell_size + 0.01 * cell_size);
    }
    if(config.is_left_braces_pressed)
    {
        Set_cell_size(cell_size - 0.01 * cell_size);
    }

#define DELTA_MOVE 10 / cell_size

    if(config.is_up_arrow_pressed)
    {
        Set_view_center_position(view_center_position + Vector2(0, -DELTA_MOVE));
    }
    if(config.is_down_arrow_pressed)
    {
        Set_view_center_position(view_center_position + Vector2(0, DELTA_MOVE));
    }
    if(config.is_left_arrow_pressed)
    {
        Set_view_center_position(view_center_position + Vector2(-DELTA_MOVE, 0));
    }
    if(config.is_right_arrow_pressed)
    {
        Set_view_center_position(view_center_position + Vector2(DELTA_MOVE, 0));
    }

#undef DELTA_MOVE

    // 更新视野的边角位置
    // view_left_top_position     = view_center_position - view_size_half;
    // view_right_bottom_position = view_center_position + view_size_half;

    // 更新相机的边角位置
    camera_left_top_position     = view_center_position - camera_size_half;
    camera_right_bottom_position = view_center_position + camera_size_half;

    // 更新鼠标
    on_update_map_mouse();

    // 更新地图细胞
    on_update_map_cells();

    // 更新星球
    if(config.is_space_pressed)
    {
        planet_manager.Set_planets0_pos(mouse_map_pos);
    }
    if(config.is_minus_pressed)
    {
        planet_manager.Set_planets0_radius(planet_manager.Get_planets()[0].Get_planet_radius() - 0.1);
    }
    if(config.is_plus_pressed)
    {
        planet_manager.Set_planets0_radius(planet_manager.Get_planets()[0].Get_planet_radius() + 0.1);
    }
    planet_manager.On_update(delta_time);

    // // 更新鸟
    // bird_manager.On_update(delta_time);

    // 更新test_rect
    on_update_test_rect();

    // 重置地图纹理大小
    painter.Destroy_texture(life_game_map_texture);
    painter.Create_texture(life_game_map_texture, map_size.px, map_size.py);
}

void
LifeGameMap::On_render() const
{
    float cell_size = life_map_view.Get_unit_size();

    Vector2 view_center_position = life_map_view.Get_view_center_position();
    Vector2 view_size_half       = life_map_view.Get_view_size_half();

    Vector2 view_left_top_position     = life_map_view.Get_view_left_top_position();
    Vector2 view_right_bottom_position = life_map_view.Get_view_right_bottom_position();

    // 设置渲染目标为地图纹理
    painter.Render_target(life_game_map_texture, &life_map_view);

    // painter.Render_clear(0x333333ff);
    painter.Render_clear({ 0x33, 0x33, 0x33, 0xff });

    // 绘制地图线
    painter.Draw_plaid();
    painter.DrawLine(1, +1, 0, 0x9999ccFF);
    painter.DrawLine(1, -1, 0, 0xcc9999FF);

    on_render_map_cells();

    // // 绘制鸟
    // BirdManager::Instance().On_render();

    // 绘制星球
    // PlanetManager::Instance().On_render();

    // 绘制test_rect
    on_render_test_rect();

    // 绘制test_rect中的行星
    draw_planet_in_test_rect_II();

    on_render_map_mouse();

    Vector2 rect_pos = { 0, 0 }; // 世界坐标
    painter.DrawCircle(rect_pos.vx, rect_pos.vy, 0.5, { 0xff, 0x99, 0x99, 0x88 }, true);

    // 恢复渲染目标为屏幕
    painter.Render_target();
}
