
// life_game_map.h

#pragma once

#include "imgui_setup.h"

class LifeGameMap : public InstanceTem<LifeGameMap>
{
    friend class InstanceTem<LifeGameMap>;

public:
    struct Cell // 细胞
    {
        Point idx; // 索引

        bool is_alive  = false;
        bool is_marked = false; // 是否被标记

        int count = 0; // 数量

        Color cell_color; //= { 0.75, 0.75, 0.75, 1.0f };

        bool operator==(const Cell& cell) const;
        bool operator<(const Cell& cell) const;

        bool operator==(const Point& p) const;
        bool operator<(const Point& p) const;
    };

    typedef std::vector<Cell> MapCells;

public:
    void On_update(float delta_time);
    void On_render() const;

public:
    const Vector2& Get_view_center_position() const;
    const Vector2& Get_view_size() const;
    const Vector2& Get_view_size_half() const;
    const Vector2& Get_view_left_top_position() const;
    const Vector2& Get_view_right_bottom_position() const;
    const Point&   Get_map_size() const;

    const Vector2& Get_camera_left_top_position() const;
    const Vector2& Get_camera_right_bottom_position() const;

    float Get_cell_size();

    bool           Is_mouse_in_map() const;
    const Vector2& Get_mouse_map_pos() const;
    const Point&   Get_selected_cell_idx() const;

public:
    Point mouse_win; // 鼠标窗口坐标

private:
    Vector2 mouse_map_pos;

private:
    bool    is_mouse_in_map = false;
    Vector2 selected_cell_map_pos; // 选中的细胞位置（左上角）
    Point   selected_cell_idx;     // 选中的细胞索引

public:
    void Set_view_center_position(const Vector2& pos);

    void Set_map_size(const Point& size);
    void Set_cell_size(float size);
    void Set_camera_size(float size);

    const View* Get_life_map_view() const;

private:
    View life_map_view; // 地图视野

    float camera_size_ratio = 0; // 相机大小比例

    Vector2 camera_size;                  // 相机大小
    Vector2 camera_size_half;             // 相机大小的一半
    Vector2 camera_left_top_position;     // 相机左上角位置
    Vector2 camera_right_bottom_position; // 相机右下角位置

    Point map_size; // 地图宽高（显示在屏幕上的）

public:
    const MapCells& Get_map_cells() const;

    Cell* Get_cell(Point idx);
    void  Del_cell(Point idx);
    void  Del_cell(Cell* cell);

private:
    MapCells map_cells; // 地图上的细胞

public:
    const Texture* Get_life_game_map_texture() const;

private:
    Texture* life_game_map_texture = nullptr;

private:
    void on_update_map_mouse();
    void on_update_map_cells();

    void on_render_map_cells() const; // 绘制地图细胞
    void on_render_map_mouse() const; // 绘制地图鼠标

private:
    LifeGameMap();
    ~LifeGameMap() = default;
};
