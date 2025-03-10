
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

    is_running = true;
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
sakaengine::NewFrame()
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    static SDL_Event sdl_event;
    while(SDL_PollEvent(&sdl_event))
    {
        if(sdl_event.type == SDL_QUIT) is_running = false;
        ImGui_ImplSDL2_ProcessEvent(&sdl_event);
    }
}


void
sakaengine::EndFrame()
{
    SDL_SetRenderTarget(sdl_renderer, nullptr);

    if(draw_background_callback)
    {
        draw_background_callback();
    }
    else
    {
        SDL_SetRenderDrawColor(sdl_renderer, clear_color.r, clear_color.g, clear_color.b, clear_color.a);
        SDL_RenderClear(sdl_renderer);
    }

    ImGui::Render();                                                                                                      // Rendering
    SDL_RenderSetScale(sdl_renderer, ImGui::GetIO().DisplayFramebufferScale.x, ImGui::GetIO().DisplayFramebufferScale.y); // 设置渲染目标
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), sdl_renderer);                                            // 渲染imgui
    SDL_RenderPresent(sdl_renderer);                                                                                      // 显示渲染结果
}


bool
sakaengine::IsInit()
{
    return init_flag == INIT_FLAG_SUCCESS;
}


bool
sakaengine::IsRunning()
{
    return is_running;
}


void
sakaengine::Break()
{
    is_running = false;
}


Color&
sakaengine::GetClearColor()
{
    return clear_color;
}


void
sakaengine::SetDrawBackgroundCallback(const Callback& callback)
{
    draw_background_callback = callback;
}


void
sakaengine::GetTextureSize(Texture* texture, int32_t& w, int32_t& h)
{
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
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
