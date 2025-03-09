
// lifegame.h

#pragma once


#include "sakaengine.h"


namespace LifeGame
{


extern bool is_running; // 是否运行

extern Texture* painter_tex;  // 画板纹理
extern View     painter_view; // 画板视野

int Run();


} // namespace LifeGame
