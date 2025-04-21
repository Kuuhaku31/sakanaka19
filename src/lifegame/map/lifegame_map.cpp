
// lifegame_map.cpp

#include "lifegame_map.h"


namespace LifeGameMap
{


View   map_view          = View({ 400, 300 }, { 0, 0, 400, 300 }); // 地图视野
float  map_view_zoom     = 1.0f;                                   // 地图视野缩放
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

    LifeGameMap::map_view.SetUnitSize(map_view_zoom);        // 设置视野单位大小

    LifeGameMap::map_view.SetDisplaySize(view_display_size); // 设置视野显示大小
    LifeGameMap::map_view.MoveBy(LifeGame::move_dir.vx * LifeGame::move_speed, LifeGame::move_dir.vy * LifeGame::move_speed);
}

void
render_grid_lines(int grid_size, const Color& color)
{
    float view_left   = LifeGameMap::map_view.viewLeft();
    float view_top    = LifeGameMap::map_view.viewTop();
    float view_right  = LifeGameMap::map_view.viewRight();
    float view_bottom = LifeGameMap::map_view.viewBottom();

    for(int x = int(view_left) - int(view_left) % grid_size; x < view_right; x += grid_size)
    {
        SKE::DrawLine(Vector2(x, view_top), Vector2(x, view_bottom), color);
    }

    for(int y = int(view_top) - int(view_top) % grid_size; y < view_bottom; y += grid_size)
    {
        SKE::DrawLine(Vector2(view_left, y), Vector2(view_right, y), color);
    }
}

void
LifeGameMap::OnRender()
{
    SKE::SetRenderTarget(map_tex, &map_view);                                // 设置渲染目标
    SKE::SetViewOffset(&view_offset);                                        // 设置视野偏移

    SKE::RenderClear({ 0x33, 0x33, 0x33, 0xff });                            // 清屏

    SKE::DrawRect(map_view.rect(), { 0x11, 0x11, 0x11, 0xff }, false);       // 绘制背景
    render_grid_lines(50, { 0x99, 0x99, 0x00, 0xff });                       // 绘制网格线

    SKE::DrawRect({ 10, 10, 100, 200 }, { 0xd0, 0xd0, 0xd0, 0xff }, false);  //
    SKE::DrawRect({ 160, -40, 50, 100 }, { 0xd0, 0xd0, 0xd0, 0xff }, false); //


    SKE::DrawLine(1, +1, 0, { 0x99, 0x99, 0xcc, 0xff });
    SKE::DrawLine(1, -1, 0, { 0xcc, 0x99, 0x99, 0xff });
    SKE::DrawLine(1, 1.5, 100, { 0xcc, 0x99, 0x99, 0xff });
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
