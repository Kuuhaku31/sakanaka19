
// lifegame.h

#pragma once

#include "sakaengine.h"


namespace LifeGame
{


extern float   move_speed; // 移动速度
extern Vector2 move_dir;   // 移动方向

extern bool is_show_view;  // 是否显示生命游戏地图


int Run();

void ProcessEvent();                 // 处理事件
void ProcessInitConfig(cJSON* root); // 处理初始化配置
void ProcessSaveConfig(cJSON* root); // 处理保存配置

} // namespace LifeGame
