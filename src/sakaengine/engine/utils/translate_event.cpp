
// translate_event.cpp

#include "utils.h"


// 翻译事件
void
translateEvent(sakaengine::Event& event, const SDL_Event& sdl_event)
{
    using E = sakaengine::Event;

    switch(sdl_event.type)
    {
        // 退出程序事件
    case SDL_QUIT:
        event.type = E::quit;
        break;

        // 按键按下
    case SDL_KEYDOWN:
        event.type = E::key_down;
        event.key  = sdl_event.key.keysym.scancode;
        break;

        // 按键抬起
    case SDL_KEYUP:
        event.type = E::key_up;
        event.key  = sdl_event.key.keysym.scancode;
        break;

        // 鼠标滚轮
    case SDL_MOUSEWHEEL:
        event.type     = E::mouse_wheel;
        event.mouse_dw = sdl_event.wheel.y;
        break;

        // 鼠标移动
    case SDL_MOUSEMOTION:
        event.type     = E::mouse_move;
        event.mouse_dx = sdl_event.motion.xrel;
        event.mouse_dy = sdl_event.motion.yrel;
        break;

    default:
        break;
    }
}
