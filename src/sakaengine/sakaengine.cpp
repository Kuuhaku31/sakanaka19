
// sakaengine.cpp

#include "sakaengine.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


namespace
{


SDL_Window*   sdl_window   = nullptr;
SDL_Renderer* sdl_renderer = nullptr;

Color clear_color;

enum InitFlag
{
    INIT_FLAG_UNINITIALIZED,
    INIT_FLAG_SUCCESS,
    INIT_FLAG_FAILED,
};
InitFlag init_flag = INIT_FLAG_UNINITIALIZED;

} // namespace


// 翻译事件
void
translateEvent(SKE::Event& event, const SDL_Event& sdl_event)
{
    using E = SKE::Event;

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


void
init() // Setup SDL
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        init_flag = INIT_FLAG_FAILED;
        printf("Error: %s\n", SDL_GetError());
    }
    if(SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1") == SDL_FALSE)
    {
        init_flag = INIT_FLAG_FAILED;
        printf("Error: %s\n", SDL_GetError());
    }
    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        init_flag = INIT_FLAG_FAILED;
        printf("Error: %s\n", IMG_GetError());
    }
    if(Mix_Init(MIX_INIT_MP3) == 0)
    {
        init_flag = INIT_FLAG_FAILED;
        printf("Error: %s\n", Mix_GetError());
    }
    if(TTF_Init() == -1)
    {
        init_flag = INIT_FLAG_FAILED;
        printf("Error: %s\n", TTF_GetError());
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        init_flag = INIT_FLAG_FAILED;
        printf("Error: %s\n", Mix_GetError());
    }
}


void
make_sdl_window(std::string& title, const IRect& layout, bool is_centered)
{
    sdl_window = SDL_CreateWindow(
        title.empty() ? "SDL2 ImGui" : title.c_str(),
        is_centered ? SDL_WINDOWPOS_CENTERED : layout.x,
        is_centered ? SDL_WINDOWPOS_CENTERED : layout.y,
        layout.w,
        layout.h,
        (SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI)

    );

    if(sdl_window == nullptr)
    {
        init_flag = INIT_FLAG_FAILED;
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
    }
}


void
make_sdl_renderer()
{
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if(sdl_renderer == nullptr)
    {
        init_flag = INIT_FLAG_FAILED;
        printf("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
    }
}


void
init_imgui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO imgui_io = ImGui::GetIO();
    imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    imgui_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    imgui_io.Fonts->AddFontDefault();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    if(!ImGui_ImplSDL2_InitForSDLRenderer(sdl_window, sdl_renderer))
    {
        init_flag = INIT_FLAG_FAILED;
        printf("Error: ImGui_ImplSDL2_InitForSDLRenderer(): %s\n", SDL_GetError());
    }
    if(!ImGui_ImplSDLRenderer2_Init(sdl_renderer))
    {
        init_flag = INIT_FLAG_FAILED;
        printf("Error: ImGui_ImplSDLRenderer2_Init(): %s\n", SDL_GetError());
    }
}


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
}


void
sakaengine::Quit()
{
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
