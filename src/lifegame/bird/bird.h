
// object.h

#pragma once

#include "tools.h"

class Bird : public Object
{
public:
    typedef std::vector<Bird*> ViewBirds;

public:
    Bird(const Vector2& pos = { 0, 0 }, const Vector2& vel = { 0, 0 }, Color color = { 0, 0, 0, 255 });
    ~Bird() = default;

public:
    void On_update(float delta_time) override;
    void On_render() const;

    void Set_id(int id);
    void Set_view_range(float range);

    int          Get_id() const;
    const Point& Get_tile_idx() const;
    float        Get_view_range() const;

    const ViewBirds& Get_view_birds() const;

private:
    int   bird_id = 0;
    Point tile_idx;
    float view_range = 1.5;

    std::vector<Point> view_cell_idxs; // 视野内的格子
    ViewBirds          view_birds;     // 视野内的对象

private:
    void on_update_with_planet(float delta_time);

private:
    bool is_intersect_tile(const Vector2 rect_center, float rect_wide, float rect_high) const; // 判断是否与某个矩形相交

    void find_view_cells();
    void find_view_birds();
};
