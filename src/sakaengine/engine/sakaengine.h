
// sakaengine.h

#pragma once

#include "engine_classes.h"


namespace sakaengine
{

void Init(EngineInitArgs& args);                                               // 初始化引擎
void Quit();                                                                   // 退出引擎

void LoadConfig(const std::string& path, std::function<void(cJSON*)> process); // 加载配置
void SaveConfig(const std::string& path, std::function<void(cJSON*)> process); // 保存配置


void NewFrame();      // 新帧
void EndFrame();      // 结束帧

bool IsInit();        // 是否初始化成功
bool IsRunning();     // 是否运行中
void Break();         // 停止运行

float GetDeltaTime(); // 获取时间间隔

Color& GetClearColor();
void   SetDrawBackgroundCallback(const Callback& callback); // 设置绘制背景回调

void SetViewOffset(const Offset* offset);                   // 设置视野偏移

// 工具
Size GetTextureSize(Texture* texture);                                        // 获取纹理大小

void CreateTexture(Texture*& texture, const Size& size);                      // 创建纹理
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
