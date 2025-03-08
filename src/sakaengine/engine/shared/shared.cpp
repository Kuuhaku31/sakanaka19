
// shared.cpp

#include "shared.h"

// 定义全局变量
SDL_Window*   sdl_window   = nullptr;
SDL_Renderer* sdl_renderer = nullptr;

Color clear_color = { 0, 0, 0, 255 };

InitFlag init_flag = INIT_FLAG_UNINITIALIZED;

// 资源池
TexturePool   texture_pool;
FontPool      font_pool;
SoundPool     sound_pool;
MusicPool     music_pool;
AnimationPool animation_pool;
