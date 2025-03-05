
// planet.h

#pragma once

#include "tools.h"

#include "life_game_map.h"

class Planet : public Object
{
public:
    Planet(const Vector2& pos = { 0, 0 }, float planet_radius = 0, Color color = { 0, 0, 0, 255 });
    ~Planet() = default;

public:
    void On_update(float delta_time) override;
    void On_render() const override;

public:
    void Set_planet_radius(float radius);

    float Get_planet_radius() const;
    float Get_planet_radius_square() const;

    const std::vector<Point>& Get_planet_tiles_idxs() const;

    bool Is_near_planet_surface(const Point& pos) const;

private:
    float planet_radius        = 0; // 半径
    float planet_radius_square = 0; // 半径的平方

private:
    std::vector<Point> planet_tiles_idxs; // 星球边界上的tile索引

private:
    void set_cell(const Point& p);
    void find_planet_tiles(); // 查找星球边界上的tile
};
