
// events.h

#pragma once


// 0b0000 0000 0000 0001
#define SKE_EVENT_QUIT 0x0001


namespace sakaengine
{


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
