
// life_game_map.cpp

#include "life_game_map.h"

#include "bird_manager.h"
#include "config.h"

#include <algorithm>

static Config& config = Config::Instance();

bool
LifeGameMap::Cell::operator<(const LifeGameMap::Cell& cell) const
{
    return idx < cell.idx;
}

bool
LifeGameMap::Cell::operator==(const LifeGameMap::Cell& cell) const
{
    return idx == cell.idx;
}

bool
LifeGameMap::Cell::operator<(const Point& p) const
{
    return idx < p;
}

bool
LifeGameMap::Cell::operator==(const Point& p) const
{
    return idx == p;
}


LifeGameMap::LifeGameMap()
{
    Set_map_size(config.map_size);
    Set_cell_size(config.cell_size);
    Set_camera_size(config.camera_size_ratio);
}

void
LifeGameMap::Set_view_center_position(const Vector2& pos)
{
    // view_center_position = pos;

    // view_left_top_position     = view_center_position - view_size_half;
    // view_right_bottom_position = view_center_position + view_size_half;

    // camera_left_top_position     = view_center_position - camera_size_half;
    // camera_right_bottom_position = view_center_position + camera_size_half;

    life_map_view.Set_view_center_position(pos);

    camera_left_top_position     = life_map_view.Get_view_center_position() - camera_size_half;
    camera_right_bottom_position = life_map_view.Get_view_center_position() + camera_size_half;
}

void
LifeGameMap::Set_map_size(const Point& size)
{
    map_size = size;

    // view_size      = (Vector2)map_size / cell_size;
    // view_size_half = view_size / 2;

    // view_left_top_position     = view_center_position - view_size_half;
    // view_right_bottom_position = view_center_position + view_size_half;

    // camera_size      = view_size * camera_size_ratio;
    // camera_size_half = view_size_half * camera_size_ratio;

    // camera_left_top_position     = view_center_position - camera_size_half;
    // camera_right_bottom_position = view_center_position + camera_size_half;

    life_map_view.Set_view_size((Vector2)map_size / life_map_view.Get_unit_size());

    camera_size      = life_map_view.Get_view_size() * camera_size_ratio;
    camera_size_half = life_map_view.Get_view_size_half() * camera_size_ratio;

    camera_left_top_position     = life_map_view.Get_view_center_position() - camera_size_half;
    camera_right_bottom_position = life_map_view.Get_view_center_position() + camera_size_half;
}

void
LifeGameMap::Set_cell_size(float size)
{
    // cell_size = size;

    // view_size      = (Vector2)map_size / cell_size;
    // view_size_half = view_size / 2;

    // view_left_top_position     = view_center_position - view_size_half;
    // view_right_bottom_position = view_center_position + view_size_half;

    // camera_size      = view_size * camera_size_ratio;
    // camera_size_half = view_size_half * camera_size_ratio;

    // camera_left_top_position     = view_center_position - camera_size_half;
    // camera_right_bottom_position = view_center_position + camera_size_half;

    life_map_view.Set_unit_size(size);

    life_map_view.Set_view_size((Vector2)map_size / life_map_view.Get_unit_size());

    camera_size      = life_map_view.Get_view_size() * camera_size_ratio;
    camera_size_half = life_map_view.Get_view_size_half() * camera_size_ratio;

    camera_left_top_position     = life_map_view.Get_view_center_position() - camera_size_half;
    camera_right_bottom_position = life_map_view.Get_view_center_position() + camera_size_half;
}

void
LifeGameMap::Set_camera_size(float size)
{
    camera_size_ratio = size;

    // camera_size      = view_size * camera_size_ratio;
    // camera_size_half = view_size_half * camera_size_ratio;

    // camera_left_top_position     = view_center_position - camera_size_half;
    // camera_right_bottom_position = view_center_position + camera_size_half;

    camera_size      = life_map_view.Get_view_size() * camera_size_ratio;
    camera_size_half = life_map_view.Get_view_size_half() * camera_size_ratio;

    camera_left_top_position     = life_map_view.Get_view_center_position() - camera_size_half;
    camera_right_bottom_position = life_map_view.Get_view_center_position() + camera_size_half;
}

const View*
LifeGameMap::Get_life_map_view() const
{
    return &life_map_view;
}

const Vector2&
LifeGameMap::Get_view_center_position() const
{
    return life_map_view.Get_view_center_position();
}

const Vector2&
LifeGameMap::Get_view_size() const
{
    return life_map_view.Get_view_size();
}

const Vector2&
LifeGameMap::Get_view_size_half() const
{
    return life_map_view.Get_view_size_half();
}

const Vector2&
LifeGameMap::Get_view_left_top_position() const
{
    return life_map_view.Get_view_left_top_position();
}

const Vector2&
LifeGameMap::Get_view_right_bottom_position() const
{
    return life_map_view.Get_view_right_bottom_position();
}

const Point&
LifeGameMap::Get_map_size() const
{
    return map_size;
}

const Vector2&
LifeGameMap::Get_camera_left_top_position() const
{
    return camera_left_top_position;
}

const Vector2&
LifeGameMap::Get_camera_right_bottom_position() const
{
    return camera_right_bottom_position;
}

const Texture*
LifeGameMap::Get_life_game_map_texture() const
{
    return life_game_map_texture;
}

float
LifeGameMap::Get_cell_size()
{
    return life_map_view.Get_unit_size();
}

bool
LifeGameMap::Is_mouse_in_map() const
{
    return is_mouse_in_map;
}

const Vector2&
LifeGameMap::Get_mouse_map_pos() const
{
    return mouse_map_pos;
}

const Point&
LifeGameMap::Get_selected_cell_idx() const
{
    return selected_cell_idx;
}


const LifeGameMap::MapCells&
LifeGameMap::Get_map_cells() const
{
    return map_cells;
}

LifeGameMap::Cell*
LifeGameMap::Get_cell(Point idx)
{
    // 遍历所有细胞
    for(Cell& cell : map_cells)
    {
        if(cell.idx == idx) // 如果找到了相等的元素，返回
        {
            return &cell;
        }
    }

    // 如果没有找到编号为 idx 的 cell， 添加到 map_cells
    map_cells.push_back(Cell{ idx });
    return &map_cells.back();
}

void
LifeGameMap::Del_cell(Point idx)
{
    // 遍历所有细胞
    for(auto it = map_cells.begin(); it != map_cells.end(); ++it)
    {
        if((*it).idx == idx) // 如果找到了相等的元素，删除
        {
            map_cells.erase(it);
            return;
        }
    }
}

void
LifeGameMap::Del_cell(Cell* cell)
{
    // 遍历所有细胞
    for(auto it = map_cells.begin(); it != map_cells.end(); ++it)
    {
        if(&(*it) == cell) // 如果找到了相等的元素，删除
        {
            map_cells.erase(it);
            return;
        }
    }
}
