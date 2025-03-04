
// base.h

#pragma once

#include <stdint.h>

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

struct Point
{
    int32_t px = 0;
    int32_t py = 0;

    Point& operator=(const Point& p)
    {
        px = p.px;
        py = p.py;

        return *this;
    }
};
#define ORIGIN_POINT Point{ 0, 0 }

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    Color&
    operator=(const Color& color)
    {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;

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

    void rotate(float angle);
    void to_unit();
    void to_zero();

    float module() const;

    bool approx_zero() const;
};
#define VECTOR2_ZERO Vector2{ 0.0f, 0.0f }
#define VECTOR2_UNIT_UP Vector2{ 0.0f, -1.0f }
#define VECTOR2_UNIT_DOWN Vector2{ 0.0f, 1.0f }
#define VECTOR2_UNIT_LEFT Vector2{ -1.0f, 0.0f }
#define VECTOR2_UNIT_RIGHT Vector2{ 1.0f, 0.0f }


template<typename Tem>
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


// 视野
class View
{
public:
    void Set_view_center_position(const Vector2& pos);
    void Set_view_size(const Vector2& size);
    void Set_unit_size(float size);

    const Vector2& Get_view_center_position() const;
    const Vector2& Get_view_size() const;
    const Vector2& Get_view_size_half() const;
    const Vector2& Get_view_left_top_position() const;
    const Vector2& Get_view_right_bottom_position() const;

    const float& Get_unit_size() const;

private:
    Vector2 view_center_position;       // 视野中心位置
    Vector2 view_size;                  // 视野宽高
    Vector2 view_size_half;             // 视野宽高的一半
    Vector2 view_left_top_position;     // 视野左上角位置
    Vector2 view_right_bottom_position; // 视野右下角位置

    float unit_size = 1.0f; // 一个单位长度的大小（像素）
};


// 单例模板
template<typename Tem>
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

template<typename Tem>
Tem* InstanceTem<Tem>::instance = nullptr;
