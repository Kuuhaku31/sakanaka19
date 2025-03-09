
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


// 工具
void GetTextureSize(Texture* texture, int32_t& w, int32_t& h); // 获取纹理大小

void DrawTexture(Texture* texture, const IRect& rect_src, const FRect& rect_dst, float angle = 0.0f); // 绘制纹理


} // namespace sakaengine


namespace SKE = sakaengine;
