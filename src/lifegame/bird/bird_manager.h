
// bird_manager.h

#pragma once

#include "life_game_map.h"

#include "bird.h"

class BirdManager : public InstanceTem<BirdManager>
{
    friend class InstanceTem<BirdManager>;

public:
    typedef std::vector<Bird>  Birds;
    typedef std::vector<Bird*> BirdList;

public:
    struct BirdTile
    {
        LifeGameMap::Cell* cell = nullptr;
        std::vector<Bird*> tile_birds;

        bool operator==(const BirdTile& tile) const;
        bool operator<(const BirdTile& tile) const;

        bool operator==(const LifeGameMap::Cell* c) const;
        bool operator<(const LifeGameMap::Cell* c) const;
    };

    typedef std::vector<BirdTile> BirdTiles;

public:
    void On_update(float delta_time);
    void On_render();

    void Tile_add_bird(Point idx, Bird* bird);    // 为某个tile添加一个bird指针
    void Tile_remove_bird(Point idx, Bird* bird); // 移除某个tile的bird指针
    bool Tile_find_bird(Point idx, Bird* bird);   // 在某个tile中查找某个bird是否存在

    const BirdList& Tile_find_birds(Point idx) const; // 在某个tile中查找所有的bird

    const BirdTiles& Get_bird_tiles() const;

public:
    Vector2 birds_target; // 鸟的目标点

    bool is_birds_goto_target = false; // 是否让鸟飞向目标点

    bool is_show_bird      = true;  // 是否显示鸟
    bool is_show_bird_view = false; // 是否显示鸟的视野范围
    bool is_show_bird_line = false; // 是否显示鸟的连接线
    bool is_show_bird_tile = true;  // 是否显示鸟所在的tile

private:
    Birds     birds;
    BirdTiles bird_tiles;

private:
    BirdManager();
    ~BirdManager() = default;
};
