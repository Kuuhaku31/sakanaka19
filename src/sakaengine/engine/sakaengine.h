
// sakaengine.h

#pragma once

#include "engine_classes.h"


typedef std::function<void(const sakaengine::Event&)> EventCallback; // 事件回调函数


namespace sakaengine
{


extern bool is_running; // 是否运行


void Init(EngineInitArgs& args); // 初始化引擎
void Quit();                     // 退出引擎

void NewFrame(); // 新帧
void EndFrame(); // 结束帧

void DrawBackground(Callback f = nullptr); // 绘制背景


bool   IsInit(); // 是否初始化成功
Color& GetClearColor();


// 工具
void GetTextureSize(Texture* texture, int32_t& w, int32_t& h); // 获取纹理大小

void CreateTexture(Texture*& texture, int32_t tex_wide, int32_t tex_high);    // 创建纹理
void DestroyTexture(Texture*& texture);                                       // 销毁纹理
void SetRenderTarget(Texture* texture = nullptr, const View* view = nullptr); // 设置渲染目标
void SetRenderColor(const Color& color = COLOR_BLACK);                        // 渲染颜色
void RenderClear(const Color& color);                                         // 清屏
void RenderClear();                                                           // 清屏

// 绘制图形
void DrawLine(float A, float B, float C, const Color& color = COLOR_BLACK); // 直线方程 Ax + By + C = 0
void DrawLine(Vector2 start, Vector2 end, const Color& color = COLOR_BLACK);
void DrawArc(const Vector2& center, float radius, float start_angle, float end_angle, const Color& color = COLOR_BLACK);

void DrawCircle(const Vector2& center, float radius, const Color& color = COLOR_BLACK, bool is_solid = true);
void DrawRect(const FRect& rect, const Color& color = COLOR_BLACK, bool is_solid = true);
void DrawTriangle(const Vector2& a, const Vector2& b, const Vector2& c, const Color& color = COLOR_BLACK, bool is_solid = true);
void DrawTexture(Texture* texture, const IRect& rect_src, const FRect& rect_dst, float angle = 0.0f);


} // namespace sakaengine


namespace SKE = sakaengine;
