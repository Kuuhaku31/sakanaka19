
// engine_classes.h

#pragma once

#include "base.h"


// 0b0000 0000 0000 0001
#define SKE_EVENT_QUIT 0x0001


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


// 事件
struct Event
{
    enum
    {
        unknown, // 未知事件

        quit,  // 结束程序事件
        exit,  // 退出事件
        enter, // 进入事件

        key_click, // 按键点击
        key_down,  // 按键按下
        key_press, // 按键按住
        key_up,    // 按键抬起

        mouse_wheel, // 鼠标滚轮
        mouse_move,  // 鼠标移动
    } type = unknown;

    uint32_t key = 0; // 按键扫描码

    int32_t mouse_dx = 0; // 鼠标 x 轴移动距离
    int32_t mouse_dy = 0; // 鼠标 y 轴移动距离
    int32_t mouse_dw = 0; // 鼠标滚轮滚动距离
};


}; // namespace sakaengine
