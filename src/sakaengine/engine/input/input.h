
// input.h

#pragma once

#include "event_names.h"

#include <SDL2/SDL.h>


namespace sakaengine
{


extern KeyState KeyStates[1024];
extern struct Mouse
{
    int32_t x  = 0;
    int32_t y  = 0;
    int32_t dx = 0;
    int32_t dy = 0;

    int32_t mouse_dw = 0; // 鼠标滚轮滚动距离

    bool is_move = false;

} mouse;


void sakaengine_ProcessEvent(SDL_Event* sdl_event);


} // namespace sakaengine