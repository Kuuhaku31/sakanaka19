
// shared.h

#pragma once

#include "utils.h"


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
