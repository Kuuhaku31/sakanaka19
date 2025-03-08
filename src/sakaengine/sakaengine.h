
// sakaengine.h

#pragma once

#include "base.h"
#include "events.h"

#include <string>


namespace SKE = sakaengine;


typedef std::function<void(const SKE::Event&)> EventCallback; // 事件回调函数


namespace sakaengine
{


// 启动参数
struct EngineInitArgs
{
    // 窗口
    std::string graph_title;                 // 窗口标题
    IRect       graph_layout;                // 窗口布局
    bool        graph_is_centered   = false; // 是否居中
    bool        graph_is_fullscreen = false; // 是否全屏

    // 资源
    std::string resources_path; // 资源路径

    // 其他
    bool is_imgui_windows_dark = true; // 是否使用暗色主题
};

void Init(EngineInitArgs& args); // 初始化引擎
void Quit();                     // 退出引擎

void ProcessEvents(EventCallback f = nullptr); // 处理事件
void Render(Callback draw_windows = nullptr, Callback draw_background = nullptr);

bool   IsInit(); // 是否初始化成功
Color& GetClearColor();


} // namespace sakaengine
