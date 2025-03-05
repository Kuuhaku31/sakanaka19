
// planet.cpp

#include "planet.h"

#include "life_game_map.h"

static const Painter& painter = Painter::Instance();

Planet::Planet(const Vector2& pos, float planet_radius, Color color)
    : Object(pos, { 0, 0 }, 1.0, color)
    , planet_radius(planet_radius)
    , planet_radius_square(planet_radius * planet_radius)
{
}

void
Planet::On_update(float delta_time)
{
    Object::On_update(delta_time);

    // find_planet_tiles();
}

void
Planet::On_render() const
{
    painter.DrawCircle(movement_position.vx, movement_position.vy, planet_radius, object_color, true);
}

void
Planet::Set_planet_radius(float radius)
{
    planet_radius        = radius;
    planet_radius_square = radius * radius;
}

float
Planet::Get_planet_radius() const
{
    return planet_radius;
}

float
Planet::Get_planet_radius_square() const
{
    return planet_radius_square;
}

const std::vector<Point>&
Planet::Get_planet_tiles_idxs() const
{
    return planet_tiles_idxs;
}

bool
Planet::Is_near_planet_surface(const Point& pos) const
{
    for(const Point& p : planet_tiles_idxs)
    {
        if(p == pos) return true;
    }

    return false;
}

void
Planet::set_cell(const Point& p)
{
    static LifeGameMap& life_map = LifeGameMap::Instance();

    planet_tiles_idxs.push_back(p);

    LifeGameMap::Cell* cell = life_map.Get_cell(p);

    cell->is_alive = true;
    cell->count += 10;
    cell->cell_color = { 255, 0, 0, 255 };
}

void
Planet::find_planet_tiles()
{
    static Point center_pos;
    static Point top_pos;
    static Point down_pos;
    static Point left_pos;
    static Point right_pos;

    static Vector2 root_pos;
    static float   root_dx;
    static float   h;
    static Point   head_pos;
    static Point   tail_pos;
    static int     n_head;
    static int     n_tail;

    planet_tiles_idxs.clear();

    center_pos = (Point)movement_position;
    top_pos    = (Point)(movement_position + Vector2(0, +planet_radius));
    down_pos   = (Point)(movement_position + Vector2(0, -planet_radius));
    left_pos   = (Point)(movement_position + Vector2(-planet_radius, 0));
    right_pos  = (Point)(movement_position + Vector2(+planet_radius, 0));


    // 右半球
    root_pos = Vector2(center_pos.px + 1, movement_position.vy);
    root_dx  = root_pos.vx - movement_position.vx;
    h        = sqrt(planet_radius_square - root_dx * root_dx);
    head_pos = (Point)(root_pos + Vector2(0, h));
    tail_pos = (Point)(root_pos + Vector2(0, -h));
    n_head   = top_pos.py - head_pos.py;
    n_tail   = tail_pos.py - down_pos.py;

    while(true)
    {
        set_cell(head_pos);
        for(int i = 0; i < n_head; i++)
        {
            set_cell(head_pos + Point(-1, +i));
        }

        set_cell(tail_pos);
        for(int i = 0; i < n_tail; i++)
        {
            set_cell(tail_pos + Point(-1, -i));
        }

        if(++root_dx > planet_radius) break;

        h = sqrt(planet_radius_square - root_dx * root_dx);

        int last_head_y = head_pos.py;
        int last_tail_y = tail_pos.py;

        root_pos += Vector2(1, 0);

        head_pos = (Point)(root_pos + Vector2(0, h));
        tail_pos = (Point)(root_pos + Vector2(0, -h));

        n_head = last_head_y - head_pos.py;
        n_tail = tail_pos.py - last_tail_y;
    }

    n_head = head_pos.py - right_pos.py;
    n_tail = right_pos.py - tail_pos.py;

    for(int i = 0; i < n_head; i++)
    {
        set_cell(right_pos + Point(0, +i));
    }

    for(int i = 1; i < n_tail; i++)
    {
        set_cell(right_pos + Point(0, -i));
    }


    // 左半球
    root_pos = Vector2(center_pos.px, movement_position.vy);
    root_dx  = root_pos.vx - movement_position.vx;
    h        = sqrt(planet_radius_square - root_dx * root_dx);
    head_pos = (Point)(root_pos + Vector2(0, h));
    tail_pos = (Point)(root_pos + Vector2(0, -h));
    n_head   = top_pos.py - head_pos.py;
    n_tail   = tail_pos.py - down_pos.py;

    while(true)
    {
        set_cell(head_pos);
        for(int i = 1; i <= n_head; i++)
        {
            set_cell(head_pos + Point(0, +i));
        }

        set_cell(tail_pos);
        for(int i = 1; i <= n_tail; i++)
        {
            set_cell(tail_pos + Point(0, -i));
        }

        if(--root_dx < -planet_radius) break;

        h = sqrt(planet_radius_square - root_dx * root_dx);

        int last_head_y = head_pos.py;
        int last_tail_y = tail_pos.py;

        root_pos += Vector2(-1, 0);

        head_pos = (Point)(root_pos + Vector2(0, h));
        tail_pos = (Point)(root_pos + Vector2(0, -h));

        n_head = last_head_y - head_pos.py;
        n_tail = tail_pos.py - last_tail_y;
    }

    n_head = head_pos.py - left_pos.py;
    n_tail = left_pos.py - tail_pos.py;

    for(int i = 0; i <= n_head; i++)
    {
        set_cell(left_pos + Point(0, +i));
    }

    for(int i = 1; i <= n_tail; i++)
    {
        set_cell(left_pos + Point(0, -i));
    }
}
