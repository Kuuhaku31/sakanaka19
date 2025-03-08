
// init.cpp

#include "shared.h"


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
