
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
