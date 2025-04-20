
// lifegame.h

#pragma once

#include "sakaengine.h"


namespace LifeGame
{


extern float   move_speed;            // 移动速度
extern Vector2 move_dir;              // 移动方向

extern uint32_t view_display_size[2]; // 视野显示大小

extern bool is_show_view;             // 是否显示生命游戏地图


int Run();

void ProcessEvent(); // 处理事件

} // namespace LifeGame
