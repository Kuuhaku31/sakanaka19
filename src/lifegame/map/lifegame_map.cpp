
// lifegame_map.cpp

#include "lifegame_map.h"


namespace LifeGameMap
{


View   map_view          = View({ 400, 300 }, { 0, 0, 400, 300 }); // 地图视野
Size   display_size      = Size(800, 600);                         // 显示大小
Size   view_display_size = Size(800, 600);                         // 视野显示大小
Offset view_offset       = Offset(0, 0);                           // 视野偏移

Texture* map_tex = nullptr;                                        // 地图纹理


} // namespace LifeGameMap


void
LifeGameMap::Init()
{
    SKE::CreateTexture(map_tex, Size(800, 600)); // 创建纹理
}


void
LifeGameMap::Quit()
{
    SKE::DestroyTexture(map_tex);
}


void
LifeGameMap::OnUpdate()
{
    LifeGameMap::ReSizeTexture(display_size);                // 重置纹理大小

    LifeGameMap::map_view.SetDisplaySize(view_display_size); // 设置视野显示大小
    LifeGameMap::map_view.MoveBy(LifeGame::move_dir.vx * LifeGame::move_speed, LifeGame::move_dir.vy * LifeGame::move_speed);
}


void
LifeGameMap::OnRender()
{
    SKE::SetRenderTarget(map_tex, &map_view);                          // 设置渲染目标
    SKE::SetViewOffset(&view_offset);                                  // 设置视野偏移

    SKE::RenderClear({ 0x33, 0x33, 0x33, 0xff });                      // 清屏

    SKE::DrawRect(map_view.rect(), { 0x11, 0x11, 0x11, 0xff }, false); // 绘制背景

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

void
LifeGameMap::ReSizeTexture(const Size& size)
{
    if(map_tex) SKE::DestroyTexture(map_tex);
    SKE::CreateTexture(map_tex, size); // 创建纹理
}

View&
LifeGameMap::GetMapView()
{
    return map_view;
}


const Texture*
LifeGameMap::GetMapTex()
{
    return map_tex;
}
