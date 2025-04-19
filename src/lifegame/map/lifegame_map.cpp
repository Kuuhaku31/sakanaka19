
// lifegame_map.cpp

#include "lifegame_map.h"


namespace LifeGameMap
{


View     map_view({ 0, 0 }, { 400, 300 }, 1.0f); // 地图视野
Texture* map_tex = nullptr;                      // 地图纹理


} // namespace LifeGameMap


void
LifeGameMap::Init()
{
    SKE::CreateTexture(map_tex, 400, 300); // 创建纹理
}


void
LifeGameMap::Quit()
{
    SKE::DestroyTexture(map_tex);
}


void
LifeGameMap::OnUpdate()
{
    LifeGameMap::map_view.MoveXby(LifeGame::move_dir.vx * LifeGame::move_speed);
    LifeGameMap::map_view.MoveYby(LifeGame::move_dir.vy * LifeGame::move_speed);
}


void
LifeGameMap::OnRender()
{
    SKE::SetRenderTarget(map_tex, &map_view);     // 设置渲染目标
    SKE::RenderClear({ 0x33, 0x33, 0x33, 0xff }); // 清屏

    SKE::DrawLine(1, +1, 0, { 0x99, 0x99, 0xcc, 0xff });
    SKE::DrawLine(1, -1, 0, { 0xcc, 0x99, 0x99, 0xff });
    SKE::DrawLine(1, 1.5, 100, { 0xcc, 0x99, 0x99, 0xff });

    Vector2 view_LT_pos = map_view.Get_view_left_top_position();
    Vector2 view_RB_pos = map_view.Get_view_right_bottom_position();

    for(int x = int(view_LT_pos.vx) - int(view_LT_pos.vx) % 100; x < view_RB_pos.vx; x += 100)
    {
        SKE::DrawLine(Vector2(x, view_LT_pos.vy), Vector2(x, view_RB_pos.vy), { 0x99, 0x99, 0xcc, 0xff });
    }

    for(int y = int(view_LT_pos.vy) - int(view_LT_pos.vy) % 100; y < view_RB_pos.vy; y += 100)
    {
        SKE::DrawLine(Vector2(view_LT_pos.vx, y), Vector2(view_RB_pos.vx, y), { 0x99, 0x99, 0xcc, 0xff });
    }
}


View&
LifeGameMap::GetMapView()
{
    return map_view;
}


Texture*
LifeGameMap::GetMapTex()
{
    return map_tex;
}
