
// sakaengine.cpp

#include "sakaengine.h"

#include "shared.h"


void
sakaengine::Init(EngineInitArgs& args)
{

    init();
    make_sdl_window(args.graph_title, args.graph_layout, args.graph_is_centered);
    make_sdl_renderer();
    init_imgui();

    if(init_flag != INIT_FLAG_FAILED)
    {
        init_flag = INIT_FLAG_SUCCESS;
        printf("Sakaengine is initialized successfully!\n");
    }
    else
    {
        printf("Sakaengine is initialized failed!\n");
    }

    loadResources(args.resources_path, sdl_renderer);
}


void
sakaengine::Quit()
{
    freeResources();

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();

    ImGui::DestroyContext();

    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);

    Mix_CloseAudio(); // 关闭音频设备

    TTF_Quit(); // 退出TTF
    Mix_Quit(); // 退出Mixer
    IMG_Quit(); // 退出IMG
    SDL_Quit(); // 退出SDL
}


void
sakaengine::ProcessEvents(EventCallback f)
{
    SDL_Event sdl_event;
    while(SDL_PollEvent(&sdl_event))
    {
        if(f)
        {
            Event e;
            translateEvent(e, sdl_event);
            f(e);
        }
        ImGui_ImplSDL2_ProcessEvent(&sdl_event);
    }
}


void
sakaengine::Render(Callback draw_windows, Callback draw_background)
{
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    if(draw_windows) draw_windows();

    ImGui::Render(); // Rendering

    SDL_RenderSetScale(sdl_renderer, ImGui::GetIO().DisplayFramebufferScale.x, ImGui::GetIO().DisplayFramebufferScale.y); // 设置渲染目标

    if(draw_background)
    {
        draw_background(); // 用户自定义的回调函数，用于渲染用户自定义的内容
    }
    else
    {
        SDL_SetRenderDrawColor(sdl_renderer, clear_color.r, clear_color.g, clear_color.b, clear_color.a);
        SDL_RenderClear(sdl_renderer);
    }

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), sdl_renderer); // 渲染imgui

    SDL_RenderPresent(sdl_renderer); // 显示渲染结果
}


bool
sakaengine::IsInit()
{
    return init_flag == INIT_FLAG_SUCCESS;
}


Color&
sakaengine::GetClearColor()
{
    return clear_color;
}


void
sakaengine::GetTextureSize(Texture* texture, int32_t& w, int32_t& h)
{
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
}


void
sakaengine::DrawTexture(Texture* texture, const IRect& rect_src, const FRect& rect_dst, float angle)
{
    if(!painter_view) return;

    float view_left_top_position_x = painter_view->Get_view_left_top_position().vx;
    float view_left_top_position_y = painter_view->Get_view_left_top_position().vy;

    float unit_size = painter_view->Get_unit_size();

    static SDL_Rect src;
    static SDL_Rect dst;

    src = { rect_src.x, rect_src.y, rect_src.w, rect_src.h };

    dst.x = (rect_dst.x - view_left_top_position_x) * unit_size;
    dst.y = (rect_dst.y - view_left_top_position_y) * unit_size;
    dst.w = rect_dst.w * unit_size;
    dst.h = rect_dst.h * unit_size;

    SDL_RenderCopyEx(
        sdl_renderer,
        texture,
        &src,
        &dst,
        angle,
        nullptr,
        SDL_FLIP_NONE

    );
}


void
sakaengine::CreateTexture(Texture*& texture, int32_t tex_wide, int32_t tex_high)
{
    texture = SDL_CreateTexture(
        sdl_renderer,             // 渲染器
        SDL_PIXELFORMAT_ARGB8888, // 像素格式
        SDL_TEXTUREACCESS_TARGET, // 纹理访问方式
        tex_wide,
        tex_high

    );

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); // 设置纹理混合模式，以支持透明度
}


void
sakaengine::DestroyTexture(Texture*& texture)
{
    SDL_DestroyTexture(texture);
}


void
sakaengine::SetRenderTarget(Texture* texture, const View* view)
{
    SDL_SetRenderTarget(sdl_renderer, texture);
    if(view) painter_view = view;
}


void
sakaengine::SetRenderColor(const Color& color)
{
    SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
}


void
sakaengine::RenderClear(const Color& color)
{
    SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(sdl_renderer);
}


void
sakaengine::RenderClear()
{
    SDL_RenderClear(sdl_renderer);
}
