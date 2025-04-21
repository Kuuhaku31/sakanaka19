
// base.h

#pragma once

#include <functional>
#include <stdint.h>
#include <string>


typedef std::function<void()>                                                                   Callback;      // 回调函数
typedef std::function<void(float& dst_x, float& dst_y, const float& src_w, const float& src_h)> CorrectivePos; // 位置修正回调函数

struct Size
{
    Size() = default;
    Size(uint32_t w, uint32_t h)
        : w(w)
        , h(h)
    {
    }
    Size(int32_t w, int32_t h)
        : w(w)
        , h(h)
    {
    }

    uint32_t w = 0; // 宽度
    uint32_t h = 0; // 高度
};


struct IRect
{
    int32_t x = 0;
    int32_t y = 0;
    int32_t w = 0;
    int32_t h = 0;
};

struct FRect
{
    float x = 0;
    float y = 0;
    float w = 0;
    float h = 0;
};

class Vector2;
struct Point
{
    Point() = default;
    Point(int x, int y)
        : px(x)
        , py(y)
    {
    }

    int32_t px = 0;
    int32_t py = 0;

    Point&
    operator=(const Point& p)
    {
        px = p.px;
        py = p.py;

        return *this;
    }

    operator Vector2() const;
};
#define ORIGIN_POINT Point{ 0, 0 }


// 颜色
using ColorF = float[4];
struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {
    }
    Color(const ColorF& color)
    {
        r = static_cast<uint8_t>(color[0] * 255);
        g = static_cast<uint8_t>(color[1] * 255);
        b = static_cast<uint8_t>(color[2] * 255);
        a = static_cast<uint8_t>(color[3] * 255);
    }

    Color&
    operator=(const Color& color)
    {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;

        return *this;
    }

    Color&
    operator=(const ColorF& color)
    {
        r = static_cast<uint8_t>(color[0] * 255);
        g = static_cast<uint8_t>(color[1] * 255);
        b = static_cast<uint8_t>(color[2] * 255);
        a = static_cast<uint8_t>(color[3] * 255);

        return *this;
    }
};

void
color_to_float4(const Color& color, float* f4);
void
float4_to_color(const float* f4, Color& color);

#define COLOR_BLACK Color{ 0x00, 0x00, 0x00, 0xFF }       // 黑色
#define COLOR_WHITE Color{ 0xFF, 0xFF, 0xFF, 0xFF }       // 白色
#define COLOR_RED Color{ 0xFF, 0x00, 0x00, 0xFF }         // 红色
#define COLOR_GREEN Color{ 0x00, 0xFF, 0x00, 0xFF }       // 绿色
#define COLOR_BLUE Color{ 0x00, 0x00, 0xFF, 0xFF }        // 蓝色
#define COLOR_YELLOW Color{ 0xFF, 0xFF, 0x00, 0xFF }      // 黄色
#define COLOR_CYAN Color{ 0x00, 0xFF, 0xFF, 0xFF }        // 青色
#define COLOR_PURPLE Color{ 0xFF, 0x00, 0xFF, 0xFF }      // 紫色
#define COLOR_ORANGE Color{ 0xFF, 0xA5, 0x00, 0xFF }      // 橙色
#define COLOR_GRAY Color{ 0x80, 0x80, 0x80, 0xFF }        // 灰色
#define COLOR_DARK_GRAY Color{ 0x40, 0x40, 0x40, 0xFF }   // 深灰色
#define COLOR_LIGHT_GRAY Color{ 0xC0, 0xC0, 0xC0, 0xFF }  // 浅灰色
#define COLOR_TRANSPARENT Color{ 0x00, 0x00, 0x00, 0x00 } // 透明色


class Vector2
{
public:
    float vx = 0;
    float vy = 0;

public:
    Vector2() = default;
    Vector2(float x, float y);
    ~Vector2() = default;

public:
    Vector2 operator+(const Vector2& v) const;
    void    operator+=(const Vector2& v);
    Vector2 operator-(const Vector2& v) const;
    void    operator-=(const Vector2& v);
    float   operator*(const Vector2& v) const;
    Vector2 operator*(float f) const;
    void    operator*=(float f);
    Vector2 operator/(float f) const;
    void    operator/=(float f);

    bool operator==(const Vector2& v) const;
    bool operator!=(const Vector2& v) const;
    bool operator>(const Vector2& v) const;
    bool operator<(const Vector2& v) const;

    operator float*(); // 定义强制转换运算符，将 Vector2 转换为 float*
    operator Point() const;

    void     rotate(float angle);
    Vector2& to_unit();
    Vector2& to_zero();

    float module() const;

    bool approx_zero() const;
};
#define VECTOR2_ZERO Vector2{ 0.0f, 0.0f }
#define VECTOR2_UNIT_UP Vector2{ 0.0f, -1.0f }
#define VECTOR2_UNIT_DOWN Vector2{ 0.0f, 1.0f }
#define VECTOR2_UNIT_LEFT Vector2{ -1.0f, 0.0f }
#define VECTOR2_UNIT_RIGHT Vector2{ 1.0f, 0.0f }


template <typename Tem>
void
swap(Tem& a, Tem& b)
{
    static Tem c;

    c = a;
    a = b;
    b = c;
}

bool
operator==(const Point& a, const Point& b);

bool
operator!=(const Point& a, const Point& b);

bool
operator<(const Point& a, const Point& b);

bool
operator>(const Point& a, const Point& b);

bool
operator<=(const Point& a, const Point& b);

bool
operator>=(const Point& a, const Point& b);

Point
operator+(const Point& a, const Point& b);

Point
operator-(const Point& a, const Point& b);


class Position
{
public:
    float x = 0;
    float y = 0;

    void MoveTo(float x, float y);
    void MoveBy(float dx, float dy);
    void MoveTo(const Vector2& p);
    void MoveBy(const Vector2& d);
    void MoveTo(const Point& p);
    void MoveBy(const Point& d);
};


// 视野
class View
{
public:
    View(Size display_size, const FRect& rect);

    void MoveCenterTo(float x, float y);
    void MoveBy(float dx, float dy);

    void SetDisplaySize(Size display_size);

    void SetW(float w);
    void SetH(float h);

    void SetUnitSize(float size);

    Vector2 centerPos() const { return Vector2{ view_center_x, view_center_y }; }
    Vector2 size() const { return Vector2{ view_size_w, view_size_h }; }
    Vector2 halfSize() const { return Vector2{ view_half_w, view_half_h }; }
    FRect   rect() const { return FRect{ view_left, view_top, view_size_w, view_size_h }; }
    Size    displaySize() const { return Size{ display_w, display_h }; }

    float viewLeft() const { return view_left; }
    float viewTop() const { return view_top; }
    float viewRight() const { return view_right; }
    float viewBottom() const { return view_bottom; }
    float viewCenterX() const { return view_center_x; }
    float viewCenterY() const { return view_center_y; }

    float viewSizeW() const { return view_size_w; }
    float viewHalfW() const { return view_half_w; }
    float viewSizeH() const { return view_size_h; }
    float viewHalfH() const { return view_half_h; }

    float unitSize() const { return unit_size; }

private:
    float view_left;     // 视野左边界 x 坐标
    float view_top;      // 视野上边界 y 坐标
    float view_right;    // 视野右边界 x 坐标
    float view_bottom;   // 视野下边界 y 坐标
    float view_center_x; // 视野中心位置 x 坐标
    float view_center_y; // 视野中心位置 y 坐标

    float view_size_w;   // 视野宽度
    float view_half_w;   // 视野宽度的一半
    float view_size_h;   // 视野高度
    float view_half_h;   // 视野高度的一半

    float unit_size;     // 一个单位长度的大小（像素）

    uint32_t display_w;  // 显示大小宽度
    uint32_t display_h;  // 显示大小高度
};


// 单例模板
template <typename Tem>
class InstanceTem
{
public:
    static Tem&
    Instance()
    {
        if(instance == nullptr) instance = new Tem();
        return *instance;
    }

protected:
    InstanceTem()                              = default;
    ~InstanceTem()                             = default;
    InstanceTem(const InstanceTem&)            = delete; // 禁用拷贝构造函数
    InstanceTem& operator=(const InstanceTem&) = delete; // 禁用赋值构造函数

private:
    static Tem* instance;
};

template <typename Tem>
Tem* InstanceTem<Tem>::instance = nullptr;


// 启动参数
struct InitArgs
{
    const char* graph_title = nullptr;
    IRect       graph_rect;

    const char* resources_path = nullptr;
};
