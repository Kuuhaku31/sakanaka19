
// object.cpp

#include "bird.h"

#include "bird_manager.h"
#include "planet_manager.h"

#include "config.h"

static Config& config = Config::Instance();

static BirdManager&   bird_manager   = BirdManager::Instance();
static PlanetManager& planet_manager = PlanetManager::Instance();

static LifeGameMap& map = LifeGameMap::Instance();

Bird::Bird(const Vector2& pos, const Vector2& vel, Color color)
    : Object(pos, vel, 1.0, color)
{
}

void
Bird::On_update(float delta_time)
{
    Point new_tile_idx = (Point)movement_position;

    if(tile_idx != new_tile_idx)
    {
        bird_manager.Tile_remove_bird(tile_idx, this);
        bird_manager.Tile_add_bird(new_tile_idx, this);
        tile_idx = new_tile_idx;
    }

    find_view_cells();
    find_view_birds();

    Vector2 average_velocity; // 平均速度
    Vector2 cohesion_dir;     // 凝聚方向
    Vector2 separation_dir;   // 分离方向
    for(Bird* b : view_birds) // 遍历 view_objects
    {
        Vector2 obj_pos = b->Get_position();
        Vector2 obj_vel = b->Get_velocity();

        average_velocity += obj_vel;

        Vector2 dir  = obj_pos - movement_position;
        float   dist = dir.module();

        cohesion_dir += dir * dist;

        if(dist < view_range * config.range)
        {
            separation_dir -= dir / (dist * dist);
        }
    }

    Force(separation_dir.to_unit() * config.separation);
    Force(cohesion_dir.to_unit() * config.cohesion);

    Vector2 rotat_force = (average_velocity - movement_velocity.to_unit() * (movement_velocity.to_unit() * average_velocity)).to_unit();

    Force(rotat_force * config.rotation);

    if(movement_velocity.module() < 1)
    {
        Force(movement_velocity.to_unit() * 10);
    }

    if(bird_manager.is_birds_goto_target)
    {
        Vector2 dir = bird_manager.birds_target - movement_position;
        Force(dir.to_unit() * 1);
    }

    on_update_with_planet(delta_time); // 与星球交互

    // 父类On_update
    Object::On_update(delta_time);
}

void
Bird::On_render() const
{
    static const Painter& painter   = Painter::Instance();
    static const float&   cell_size = LifeGameMap::Instance().Get_cell_size();


    Object::On_render();

    if(bird_manager.is_show_bird_view)
    {
        painter.DrawCircle(
            movement_position.vx,
            movement_position.vy,
            view_range,
            object_color,
            true

        );
    }

    if(bird_manager.is_show_bird_line)
    {
        for(Bird* b : view_birds)
        {
            painter.DrawLine(
                movement_position.vx,
                movement_position.vy,
                b->movement_position.vx,
                b->movement_position.vy,
                object_color

            );
        }
    }
}

void
Bird::Set_id(int id)
{
    bird_id = id;
}

void
Bird::Set_view_range(float range)
{
    view_range = range;
}

int
Bird::Get_id() const
{
    return bird_id;
}

const Point&
Bird::Get_tile_idx() const
{
    return tile_idx;
}

float
Bird::Get_view_range() const
{
    return view_range;
}

const Bird::ViewBirds&
Bird::Get_view_birds() const
{
    return view_birds;
}

void
Bird::on_update_with_planet(float delta_time)
{
    const Planet& planet = planet_manager.Get_planets()[0];

    // 遍历视野内的格子
    for(Point idx : view_cell_idxs)
    {
        if(planet.Is_near_planet_surface(idx)) // 如果这个格子在星球表面上
        {
            float dist = (movement_position - planet.Get_position()).module();

            float delta = planet.Get_planet_radius() - dist;

            if(delta > 0)
            {
                Vector2 dir = movement_position - planet.Get_position();

                Force(dir.to_unit() * delta * 10); // 从星球表面施加一个力
            }
        }
    }
}

bool
Bird::is_intersect_tile(const Vector2 rect_center, float rect_wide, float rect_high) const
{
    Vector2 v = movement_position - rect_center;
    Vector2 h = Vector2(rect_wide / 2, rect_high / 2);

    if(v.vx < 0) v.vx = -v.vx;
    if(v.vy < 0) v.vy = -v.vy;

    Vector2 u = v - h;

    if(u.vx < 0) u.vx = 0;
    if(u.vy < 0) u.vy = 0;

    return u.vx * u.vx + u.vy * u.vy <= view_range * view_range;
}

void
Bird::find_view_cells()
{
    view_cell_idxs.clear();

    int view_range_int = (int)view_range + 1;

    for(int i = tile_idx.px - view_range_int; i <= tile_idx.px + view_range_int; i++)
    {
        for(int j = tile_idx.py - view_range_int; j <= tile_idx.py + view_range_int; j++)
        {
            if(is_intersect_tile(Vector2(i + 0.5f, j + 0.5f), 1, 1)) // 如果这个tile在视野范围内
            {
                view_cell_idxs.push_back({ i, j });

                LifeGameMap::Cell* cell = map.Get_cell({ i, j });

                cell->is_alive = true;
                cell->count++;
            }
        }
    }
}

void
Bird::find_view_birds()
{
    view_birds.clear();

    for(Point idx : view_cell_idxs) // 遍历 view_cell_idxs
    {
        const BirdManager::BirdList& tile_birds = bird_manager.Tile_find_birds(idx);
        for(Bird* bird : tile_birds) // 遍历 tile_birds
        {
            if(bird == this) continue; // 如果是自己，跳过

            Vector2 obj_pos = bird->Get_position();
            Vector2 dir     = obj_pos - movement_position;
            if(dir.module() <= view_range)
            {
                // 如果这个对象在视野范围内，添加到 view_objects
                view_birds.push_back(bird);
            }
        }
    }
}
