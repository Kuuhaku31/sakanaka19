
// sakaengine.h

#pragma once

#include "engine_classes.h"


typedef std::function<void(const sakaengine::Event&)> EventCallback; // 事件回调函数


namespace sakaengine
{


void Init(EngineInitArgs& args); // 初始化引擎
void Quit();                     // 退出引擎

void ProcessEvents(EventCallback f = nullptr); // 处理事件
void Render(Callback draw_windows = nullptr, Callback draw_background = nullptr);

bool   IsInit(); // 是否初始化成功
Color& GetClearColor();


} // namespace sakaengine


namespace SKE = sakaengine;
