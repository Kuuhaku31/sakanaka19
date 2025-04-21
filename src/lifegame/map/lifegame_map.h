
// lifegame_map.h

#pragma once

#include "lifegame.h"


namespace LifeGameMap
{


extern View   map_view;          // 地图视野
extern float  map_view_zoom;     // 地图视野缩放
extern Size   display_size;      // 显示大小
extern Size   view_display_size; // 视野显示大小
extern Offset view_offset;       // 视野偏移

extern Texture* map_tex;         // 地图纹理


struct Cell    // 细胞
{
    Point idx; // 索引

    bool is_alive  = false;
    bool is_marked = false; // 是否被标记

    int count = 0;          // 数量

    Color cell_color;       //= { 0.75, 0.75, 0.75, 1.0f };

    bool operator==(const Cell& cell) const;
    bool operator<(const Cell& cell) const;

    bool operator==(const Point& p) const;
    bool operator<(const Point& p) const;
};


void Init();
void Quit();

void OnUpdate();
void OnRender();

void ReSizeTexture(const Size& size); // 重置纹理大小

View&          GetMapView();
const Texture* GetMapTex();


} // namespace LifeGameMap
