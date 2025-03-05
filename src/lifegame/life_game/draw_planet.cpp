
// draw_planet.cpp

#include "draw_planet.h"

#include "config.h"
#include "planet_manager.h"

static Painter& painter = Painter::Instance();

static Config& config = Config::Instance();

static FRect   test_rect            = { 0.5, 1.7, 4, 3 };
static Vector2 test_rect_size       = { 4, 3 };
static Vector2 test_rect_size_half  = { 2, 1.5 };
static Vector2 test_rect_center     = { 0.5, 1.7 };
static Vector2 test_rect_left_top   = { 0.5, 1.7 };
static Vector2 test_rect_right_down = { 4.5, 4.7 };

void
on_update_test_rect()
{
    test_rect_size_half = test_rect_size / 2;

    test_rect            = { test_rect_center.vx - test_rect_size_half.vx, test_rect_center.vy - test_rect_size_half.vy, test_rect_size.vx, test_rect_size.vy };
    test_rect_left_top   = { test_rect_center.vx - test_rect_size_half.vx, test_rect_center.vy - test_rect_size_half.vy };
    test_rect_right_down = { test_rect_center.vx + test_rect_size_half.vx, test_rect_center.vy + test_rect_size_half.vy };
}

void
on_render_test_rect()
{
    painter.DrawRect(test_rect.x, test_rect.y, test_rect.w, test_rect.h, { 0xff, 0x0, 0xff, 0xff }, true);
}

void
draw_planet_in_test_rect()
{
    static const Planet& planet = PlanetManager::Instance().Get_planets()[0];

    // 行星中心坐标
    float planet_center_x = planet.Get_position().vx;
    float planet_center_y = planet.Get_position().vy;
    float planet_radius   = planet.Get_planet_radius();        // 行星半径
    float planet_radius_2 = planet.Get_planet_radius_square(); // 行星半径的平方

    float rect_right = test_rect_right_down.vx;
    float rect_down  = test_rect_right_down.vy;
    float rect_left  = test_rect_left_top.vx;
    float rect_top   = test_rect_left_top.vy;


    float dx_right = rect_right - planet_center_x; // 行星中心到矩形右边的距离
    float theta_r1 = 0;                            // 矩形右边与圆的可能焦点，用圆心角表示，单位为弧度
    float theta_r2 = 0;
    bool  is_r1    = false; // 是否有焦点
    bool  is_r2    = false;


    float dy_down  = rect_down - planet_center_y; // 行星中心到矩形下边的距离
    float theta_d1 = 0;                           // 矩形下边与圆的可能焦点，用圆心角表示，单位为弧度
    float theta_d2 = 0;
    bool  is_d1    = false; // 是否有焦点
    bool  is_d2    = false;


    float dx_left  = rect_left - planet_center_x; // 行星中心到矩形左边的距离
    float theta_l1 = 0;                           // 矩形左边与圆的可能焦点，用圆心角表示，单位为弧度
    float theta_l2 = 0;
    bool  is_l1    = false; // 是否有焦点
    bool  is_l2    = false;


    float dy_top   = rect_top - planet_center_y; // 行星中心到矩形上边的距离
    float theta_t1 = 0;                          // 矩形上边与圆的可能焦点，用圆心角表示，单位为弧度
    float theta_t2 = 0;
    bool  is_t1    = false; // 是否有焦点
    bool  is_t2    = false;


    if(dx_right < planet_radius) // 如果行星中心到矩形右边的距离小于行星半径
    {
        float dy = sqrt(planet_radius_2 - dx_right * dx_right); // 矩形右边与圆的焦点到行星中心的垂直距禋

        float r1 = planet_center_y - dy; // 矩形右边与圆的可能焦点1的y坐标
        float r2 = planet_center_y + dy; // 矩形右边与圆的可能焦点2的y坐标

        if(r1 > rect_top && r1 < rect_down)
        {
            theta_r1 = -acos(dx_right / planet_radius);
            is_r1    = true;

            painter.DrawLine(planet_center_x, planet_center_y, rect_right, r1, { 0xff, 0x0, 0x0, 0xff });
        }
        if(r2 > rect_top && r2 < rect_down)
        {
            theta_r2 = +acos(dx_right / planet_radius);
            is_r2    = true;

            painter.DrawLine(planet_center_x, planet_center_y, rect_right, r2, { 0xff, 0x0, 0x0, 0xff });
        }
    }

    if(dy_down < planet_radius) // 如果行星中心到矩形下边的距离小于行星半径
    {
        float dx = sqrt(planet_radius_2 - dy_down * dy_down); // 矩形下边与圆的焦点到行星中心的水平距离

        float d1 = planet_center_x + dx; // 矩形下边与圆的可能焦点1的x坐标
        float d2 = planet_center_x - dx; // 矩形下边与圆的可能焦点2的x坐标

        if(d1 > rect_left && d1 < rect_right)
        {
            theta_d1 = asin(dy_down / planet_radius);
            is_d1    = true;

            painter.DrawLine(planet_center_x, planet_center_y, d1, rect_down, { 0xff, 0x0, 0x0, 0xff });
        }

        if(d2 > rect_left && d2 < rect_right)
        {
            theta_d2 = M_PI - asin(dy_down / planet_radius);
            is_d2    = true;

            painter.DrawLine(planet_center_x, planet_center_y, d2, rect_down, { 0xff, 0x0, 0x0, 0xff });
        }
    }

    if(dx_left < planet_radius) // 如果行星中心到矩形左边的距离小于行星半径
    {
        float dy = sqrt(planet_radius_2 - dx_left * dx_left); // 矩形左边与圆的焦点到行星中心的垂直距禋

        float l1 = planet_center_y + dy; // 矩形左边与圆的可能焦点1的y坐标
        float l2 = planet_center_y - dy; // 矩形左边与圆的可能焦点2的y坐标

        if(l1 > rect_top && l1 < rect_down)
        {
            theta_l1 = +acos(dx_left / planet_radius);
            is_l1    = true;

            painter.DrawLine(planet_center_x, planet_center_y, rect_left, l1, { 0xff, 0x0, 0x0, 0xff });
        }
        if(l2 > rect_top && l2 < rect_down)
        {
            theta_l2 = -acos(dx_left / planet_radius);
            is_l2    = true;

            painter.DrawLine(planet_center_x, planet_center_y, rect_left, l2, { 0xff, 0x0, 0x0, 0xff });
        }
    }

    if(dy_top < planet_radius) // 如果行星中心到矩形上边的距离小于行星半径
    {
        float dx = sqrt(planet_radius_2 - dy_top * dy_top); // 矩形上边与圆的焦点到行星中心的水平距离

        float t1 = planet_center_x - dx; // 矩形上边与圆的可能焦点1的x坐标
        float t2 = planet_center_x + dx; // 矩形上边与圆的可能焦点2的x坐标

        if(t1 > rect_left && t1 < rect_right)
        {
            theta_t1 = M_PI - asin(dy_top / planet_radius);
            is_t1    = true;

            painter.DrawLine(planet_center_x, planet_center_y, t1, rect_top, { 0xff, 0x0, 0x0, 0xff });
        }

        if(t2 > rect_left && t2 < rect_right)
        {
            theta_t2 = asin(dy_top / planet_radius);
            is_t2    = true;

            painter.DrawLine(planet_center_x, planet_center_y, t2, rect_top, { 0xff, 0x0, 0x0, 0xff });
        }
    }


    float start_theta = 0;
    float end_theta   = 0;

    float thetas[8] = { theta_r1, theta_r2, theta_d1, theta_d2, theta_l1, theta_l2, theta_t1, theta_t2 };
    int   is_fs[8]  = { is_r1, is_r2, is_d1, is_d2, is_l1, is_l2, is_t1, is_t2 };

    int first      = -1;
    int next_is_fs = -1;
    for(int i = 7; i >= 0; i--)
    {
        if(is_fs[i])
        {
            if(next_is_fs == -1)
            {
                next_is_fs = first = i;
                continue;
            }

            is_fs[i]     = next_is_fs;
            next_is_fs   = i;
            is_fs[first] = i;
        }
        else
        {
            is_fs[i] = -1;
        }
    }

    if(first != -1) // 说明有圆和矩形有交点
    {
        if(first % 2 == 0) // 如果 first 是偶数，说明是起点是下一个交点
        {
            first = is_fs[first];
        }

        int idx = first;

        int i = 0;
        do
        {
            start_theta = thetas[idx];
            end_theta   = thetas[is_fs[idx]];

            painter.DrawArc(
                planet_center_x,
                planet_center_y,
                planet_radius,
                start_theta * 180 / M_PI,
                end_theta * 180 / M_PI,
                { 0xff, 0x0, 0x0, 0xff }

            );

            idx = is_fs[is_fs[idx]];

            i += 2;
        } while(idx != first);
    }
    else
    {
    }
}

// 判断圆是否相交或包含矩形
bool
is_intersect_tile(float circle_center_x, float circle_center_y, float circle_radius, float rect_center_x, float rect_center_y, float rect_wide, float rect_high)
{
    float dx = circle_center_x - rect_center_x;
    float dy = circle_center_y - rect_center_y;

    float h_wide = rect_wide / 2;
    float h_high = rect_high / 2;

    if(dx < 0) dx = -dx;
    if(dy < 0) dy = -dy;

    float u_x = dx - h_wide;
    float u_y = dy - h_high;

    if(u_x < 0) u_x = 0;
    if(u_y < 0) u_y = 0;

    return u_x * u_x + u_y * u_y <= circle_radius * circle_radius;
}

void
draw_planet_in_test_rect_II()
{
    static const Planet& planet = PlanetManager::Instance().Get_planets()[0];

    // 行星中心坐标
    float planet_center_x = planet.Get_position().vx;
    float planet_center_y = planet.Get_position().vy;
    float planet_radius   = planet.Get_planet_radius();        // 行星半径
    float planet_radius_2 = planet.Get_planet_radius_square(); // 行星半径的平方

    float rect_right = test_rect_right_down.vx;
    float rect_down  = test_rect_right_down.vy;
    float rect_left  = test_rect_left_top.vx;
    float rect_top   = test_rect_left_top.vy;


    float dx = planet_center_x - test_rect_center.vx;
    float dy = planet_center_y - test_rect_center.vy;

    float h_wide = test_rect_size.vx / 2;
    float h_high = test_rect_size.vy / 2;

    if(dx < 0) dx = -dx;
    if(dy < 0) dy = -dy;

    float u_x = dx - h_wide;
    float u_y = dy - h_high;

    if(u_x < 0) u_x = 0;
    if(u_y < 0) u_y = 0;

    if(u_x * u_x + u_y * u_y >= planet_radius * planet_radius)
    {
        painter.DrawCircle(planet_center_x, planet_center_y, planet_radius, { 0xff, 0x0, 0x0, 0xff }, true);
        return;
    }

    if(test_rect_size.module() / planet_radius > 0.1)
    {
        painter.DrawCircle(planet_center_x, planet_center_y, planet_radius, { 0xff, 0x0, 0x0, 0xff }, true);
    }
    else
    {
        // painter.DrawCircle(planet_center_x, planet_center_y, planet_radius, 0x0000ffff, true);

        Vector2 dir = test_rect_center - planet.Get_position();

        dir = dir.to_unit();
        dir *= planet_radius;
        dir += planet.Get_position();

        painter.DrawCircle(planet_center_x, planet_center_y, planet_radius, { 0xff, 0x0, 0x0, 0x88 }, true);

        painter.DrawLine(
            dir.vx - planet_center_x,
            dir.vy - planet_center_y,
            -planet_radius_2 - planet_center_x * (dir.vx - planet_center_x) - planet_center_y * (dir.vy - planet_center_y),
            0x0000ffff

        );
    }
}