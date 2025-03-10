
// translate_event.cpp

#include "utils.h"


// 翻译事件
void
sakaengine::sakaengine_ProcessEvent(SDL_Event* sdl_event)
{
    KeyName  keyName  = SKE_KEY_NAME_UNKNOWN;
    KeyState keyState = SKE_KEY_STATE_UNKNOWN;

    switch(sdl_event->type)
    {

    case SDL_KEYDOWN:
    {
        keyState = SKE_KEY_STATE_DOWN;

        switch(sdl_event->key.keysym.sym)
        {
        case SDLK_RETURN: keyName = SKE_KEY_NAME_RETURN; break;
        }

        break;
    }
    };
}
