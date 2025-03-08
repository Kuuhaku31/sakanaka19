
// imgui_setup.h

#pragma once

#include "base.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <string>


typedef SDL_Event    Event;
typedef SDL_Texture  Texture;
typedef SDL_Renderer Renderer;
typedef ImFont       Font;
typedef Mix_Chunk    Sound;
typedef Mix_Music    Music;

class AnimationTemplate;


// Painter
class Painter : public InstanceTem<Painter>
{
    friend class InstanceTem<Painter>;

    friend class ResourcesPool;

public:
    int Init(const char* title = nullptr, const IRect& layout = IRect{ 0, 0, 0, 0 }); // 0:初始化成功
    int Quit();

    void GetInput(std::function<void(const Event&)> f = nullptr) const;
    void Render(Callback draw_windows = nullptr, Callback draw_background = nullptr) const;

    Color clear_color;

    //====================================================================================================

    void On_frame_begin(std::function<void(const Event&)> f = nullptr) const;
    void On_frame_end(Callback f = nullptr) const;

    bool Make_message_box(const char* title, const char* message) const;

public:
    void Create_texture(Texture*& texture, int tex_wide, int tex_high) const;
    void Destroy_texture(Texture*& texture) const;

    void Render_target(Texture* texture = nullptr, const View* view = nullptr);
    void Render_color(const Color& color = COLOR_BLACK) const;
    void Render_clear(const Color& color = COLOR_BLACK) const;
    void Render_clear() const;

private:
    void draw_plaid_line(int p) const;

public:
    void Draw_plaid() const;

    void DrawLine(float A, float B, float C, const Color& color = COLOR_BLACK) const; // 直线方程 Ax + By + C = 0
    void DrawLine_(float start_x, float start_y, float end_x, float end_y, const Color& color = COLOR_BLACK) const;
    void DrawLine(float start_x, float start_y, float end_x, float end_y, const Color& color = COLOR_BLACK) const;
    void DrawArc(float center_x, float center_y, float radius, float start_angle, float end_angle, const Color& color = COLOR_BLACK) const;
    void DrawCircle(float center_x, float center_y, float radius, const Color& color = COLOR_BLACK, bool is_solid = true) const;
    void DrawRect(float x, float y, float w, float h, const Color& color = COLOR_BLACK, bool is_solid = true) const;
    void DrawTriangle(float a_x, float a_y, float b_x, float b_y, float c_x, float c_y, const Color& color = COLOR_BLACK, bool is_solid = true) const;

    void DrawTexture(Texture* texture, const IRect& rect_src, const FRect& rect_dst, float angle = 0.0f) const;

private:
    int init_flag = 1; // 1:未初始化 0:初始化成功 -1:初始化失败

    SDL_Window* window   = nullptr;
    Renderer*   renderer = nullptr;

    const View* painter_view = nullptr;
};
