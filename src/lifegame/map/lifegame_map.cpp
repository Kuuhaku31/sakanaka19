
// lifegame_map.cpp

#include "lifegame_map.h"


namespace LifeGameMap
{


View     map_view({ 0, 0, 400, 300 }, 1.0f); // 地图视野
Texture* map_tex = nullptr;                  // 地图纹理


} // namespace LifeGameMap


void
LifeGameMap::Init()
{
    SKE::CreateTexture(map_tex, 800, 600); // 创建纹理
    SKE::ViewOffset offset = { 100, 200 };
    SKE::SetViewOffset(offset);            // 设置视野偏移
}


void
LifeGameMap::Quit()
{
    SKE::DestroyTexture(map_tex);
}


void
LifeGameMap::OnUpdate()
{
    LifeGameMap::map_view.MoveBy(LifeGame::move_dir.vx * LifeGame::move_speed, LifeGame::move_dir.vy * LifeGame::move_speed);
}


void
LifeGameMap::OnRender()
{
    SKE::SetRenderTarget(map_tex, &map_view);     // 设置渲染目标
    SKE::RenderClear({ 0x33, 0x33, 0x33, 0xff }); // 清屏

    SKE::DrawLine(1, +1, 0, { 0x99, 0x99, 0xcc, 0xff });
    SKE::DrawLine(1, -1, 0, { 0xcc, 0x99, 0x99, 0xff });
    SKE::DrawLine(1, 1.5, 100, { 0xcc, 0x99, 0x99, 0xff });


    float view_left   = map_view.viewLeft();
    float view_top    = map_view.viewTop();
    float view_right  = map_view.viewRight();
    float view_bottom = map_view.viewBottom();

    for(int x = int(view_left) - int(view_left) % 100; x < view_right; x += 100)
    {
        SKE::DrawLine(Vector2(x, view_top), Vector2(x, view_bottom), { 0x99, 0x99, 0xcc, 0xff });
    }

    for(int y = int(view_top) - int(view_top) % 100; y < view_bottom; y += 100)
    {
        SKE::DrawLine(Vector2(view_left, y), Vector2(view_right, y), { 0x99, 0x99, 0xcc, 0xff });
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
