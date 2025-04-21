
// shared.h

#pragma once

#include "utils.h"


namespace sakaengine
{


extern bool is_running; // 是否运行

extern SDL_Window*   sdl_window;
extern SDL_Renderer* sdl_renderer;

extern Color clear_color;

extern InitFlag init_flag;

// 资源池
extern TexturePool   texture_pool;
extern FontPool      font_pool;
extern SoundPool     sound_pool;
extern MusicPool     music_pool;
extern AnimationPool animation_pool;

// 视野
extern const View*   painter_view;        // 视野
extern const Offset* view_offset;         // 视野偏移

extern Callback draw_background_callback; // 绘制背景回调

}; // namespace sakaengine
