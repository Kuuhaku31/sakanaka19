
// utils.h

#pragma once

#include "engine_classes.h"


#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


enum InitFlag
{
    INIT_FLAG_UNINITIALIZED,
    INIT_FLAG_SUCCESS,
    INIT_FLAG_FAILED,
};


typedef std::unordered_map<std::string, SDL_Texture*> TexturePool;
typedef std::unordered_map<std::string, ImFont*>      FontPool;
typedef std::unordered_map<std::string, Mix_Chunk*>   SoundPool;
typedef std::unordered_map<std::string, Mix_Music*>   MusicPool;
class AnimationTemplate;
typedef std::unordered_map<std::string, AnimationTemplate*> AnimationPool;


void init();
void make_sdl_window(std::string& title, const IRect& layout, bool is_centered);
void make_sdl_renderer();
void init_imgui();

void loadResources(const std::string& resources_path, SDL_Renderer* renderer);
void freeResources();
void translateEvent(sakaengine::Event& event, const SDL_Event& sdl_event);
