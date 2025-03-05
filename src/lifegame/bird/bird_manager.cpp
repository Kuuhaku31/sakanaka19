
// bird_manager.cpp

#include "bird_manager.h"

#include "config.h"

// static const Painter& painter = Painter::Instance();

// static Config&      config   = Config::Instance();
// static LifeGameMap& life_map = LifeGameMap::Instance();

// static const float&   cell_size              = life_map.Get_cell_size();
// static const Vector2& view_center_position   = life_map.Get_view_center_position();
// static const Vector2& view_left_top_position = life_map.Get_view_left_top_position();

bool
BirdManager::BirdTile::operator==(const BirdTile& tile) const
{
    return cell == tile.cell;
}

bool
BirdManager::BirdTile::operator<(const BirdTile& tile) const
{
    return cell < tile.cell;
}

bool
BirdManager::BirdTile::operator==(const LifeGameMap::Cell* c) const
{
    return cell == c;
}

bool
BirdManager::BirdTile::operator<(const LifeGameMap::Cell* c) const
{
    return cell < c;
}

BirdManager::BirdManager()
{
    // 加载 objects
    int   bird_num   = 150;
    float interval_x = 0.05;
    float RANGE_00   = 0.5;
    for(int i = 0; i < bird_num; i++)
    {
        birds.emplace_back();
        birds[i].Set_id(i);

        Vector2 pos = { interval_x * i, 0.5 };

        birds[i].Set_position(pos);

        switch(rand() % 6)
        {
        case 0:
            // birds[i].Set_color(0xff0000cc);
            birds[i].Set_color({ 255, 0, 0, 204 });
            birds[i].Set_view_range(RANGE_00);
            break;

        case 1:
            // birds[i].Set_color(0x00ff00cc);
            birds[i].Set_color({ 0, 255, 0, 204 });
            birds[i].Set_view_range(RANGE_00);
            break;

        case 2:
            // birds[i].Set_color(0x0000ffcc);
            birds[i].Set_color({ 0, 0, 255, 204 });
            birds[i].Set_view_range(RANGE_00);
            break;

        case 3:
            // birds[i].Set_color(0xff00ffcc);
            birds[i].Set_color({ 255, 0, 255, 204 });
            birds[i].Set_view_range(RANGE_00);
            break;

        case 4:
            // birds[i].Set_color(0xffff00cc);
            birds[i].Set_color({ 255, 255, 0, 204 });
            birds[i].Set_view_range(RANGE_00);
            break;

        case 5:
            // birds[i].Set_color(0x00ffffcc);
            birds[i].Set_color({ 0, 255, 255, 204 });
            birds[i].Set_view_range(RANGE_00);
            break;

        default: break;
        }

        birds[i].Set_air_resistance(0.1);
        birds[i].Set_friction(0.001);
    }
}

void
BirdManager::On_update(float delta_time)
{
    static LifeGameMap& life_map = LifeGameMap::Instance();
    static Config&      config   = Config::Instance();

    // 遍历所有的 bird
    for(Bird& bird : birds)
    {
        bird.On_update(delta_time);
    }

    if(config.is_num_1_pressed)
    {
        birds[0].Set_position(life_map.Get_mouse_map_pos());
    }

    if(config.is_T_pressed)
    {
        birds_target = life_map.Get_mouse_map_pos();
    }
}

void
BirdManager::On_render()
{
    static const Painter&     painter  = Painter::Instance();
    static const LifeGameMap& life_map = LifeGameMap::Instance();

    // 绘制 birds
    if(is_show_bird)
    {
        for(const Bird& bird : birds)
        {
            Vector2 pos = bird.Get_position();

            Vector2 c_LT_pos = life_map.Get_camera_left_top_position();
            Vector2 c_RB_pos = life_map.Get_camera_right_bottom_position();

            if(pos.vx < c_LT_pos.vx || pos.vx > c_RB_pos.vx || pos.vy < c_LT_pos.vy || pos.vy > c_RB_pos.vy)
            {
                continue;
            }

            bird.On_render();
        }
    }

    if(is_birds_goto_target)
    {
        painter.DrawCircle(birds_target.vx, birds_target.vy, 0.05, { 255, 0, 0, 255 }, true);
    }
}

void
BirdManager::Tile_add_bird(Point idx, Bird* bird)
{
    static LifeGameMap& life_map = LifeGameMap::Instance();

    // 遍历所有的 bird_tiles
    for(auto it = bird_tiles.begin(); it != bird_tiles.end(); ++it)
    {
        if((*it).cell->idx == idx) // 如果找到了相等的元素
        {
            // 添加 bird
            (*it).tile_birds.push_back(bird);

            return;
        }
    }

    // 如果没有找到编号为 idx 的 cell
    // 添加到 bird_tiles
    bird_tiles.push_back(BirdTile{ life_map.Get_cell(idx) });
    bird_tiles.back().tile_birds.push_back(bird);
}

void
BirdManager::Tile_remove_bird(Point idx, Bird* bird)
{
    static LifeGameMap& life_map = LifeGameMap::Instance();

    // 遍历所有的 bird_tiles
    for(auto it = bird_tiles.begin(); it != bird_tiles.end(); ++it)
    {
        if((*it).cell->idx == idx) // 如果找到了相等的元素
        {
            // 查找 bird
            for(auto it_bird = (*it).tile_birds.begin(); it_bird != (*it).tile_birds.end(); ++it_bird)
            {
                if(*it_bird == bird)
                {
                    // 移除 bird
                    (*it).tile_birds.erase(it_bird);

                    // 如果 tile_birds 为空
                    if((*it).tile_birds.empty())
                    {
                        life_map.Del_cell((*it).cell); // 移除 cell
                        bird_tiles.erase(it);          // 移除 tile
                    }

                    return;
                }
            }
        }
    }
}

bool
BirdManager::Tile_find_bird(Point idx, Bird* bird)
{
    // 遍历所有的 bird_tiles
    for(auto it = bird_tiles.begin(); it != bird_tiles.end(); ++it)
    {
        if((*it).cell->idx == idx) // 如果找到了相等的元素
        {
            // 查找 bird
            for(auto it_bird = (*it).tile_birds.begin(); it_bird != (*it).tile_birds.end(); ++it_bird)
            {
                if(*it_bird == bird)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

const BirdManager::BirdList&
BirdManager::Tile_find_birds(Point idx) const
{
    // 遍历所有的 bird_tiles
    for(auto it = bird_tiles.begin(); it != bird_tiles.end(); ++it)
    {
        if((*it).cell->idx == idx) // 如果找到了相等的元素
        {
            return (*it).tile_birds;
        }
    }

    static BirdList empty_list;
    return empty_list;
}

const BirdManager::BirdTiles&
BirdManager::Get_bird_tiles() const
{
    return bird_tiles;
}
