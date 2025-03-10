
// lifegame.h

#pragma once


#include "sakaengine.h"


namespace LifeGame
{


extern float   move_speed; // 移动速度
extern Vector2 move_dir;   // 移动方向


int Run();

void ProcessEvent(); // 处理事件


} // namespace LifeGame
