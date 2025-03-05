
// painter_draw_plaid.cpp

#include "imgui_setup.h"

#include "base.h"

// ABGR
#define COLOR_DEFAULT 0xFF000000
#define COLOR_BACKGROUD 0xFF333333
#define COLOR_XY_AXIS 0xFFff9999
#define COLOR_LINE_10_0 0xFF525252
#define COLOR_LINE_10_1 0xFF666666
#define COLOR_LINE_10_2 0xFFc4c4c4
#define COLOR_LINE_10_3 0xFF9b4f39
#define COLOR_LINE_10_4 0xFFcd944f
#define COLOR_LINE_10_5 0xFFe78e2e
#define COLOR_LINE_10_6 0xFF458236
#define COLOR_LINE_10_7 0xFF0000ff
#define COLOR_LINE_10_8 0xFF4bcc2b
#define COLOR_LINE_10_9 0xFF37378f
#define COLOR_LINE_10_A 0xFF8f8f8f
#define COLOR_LINE_10_B 0xFF3737df


static uint8_t  color_lines_size = 12;
static uint32_t color_lines[]    = {
    COLOR_LINE_10_0,
    COLOR_LINE_10_1,
    COLOR_LINE_10_2,
    COLOR_LINE_10_3,
    COLOR_LINE_10_4,
    COLOR_LINE_10_5,
    COLOR_LINE_10_6,
    COLOR_LINE_10_7,
    COLOR_LINE_10_8,
    COLOR_LINE_10_9,
    COLOR_LINE_10_A,
    COLOR_LINE_10_B
};

Uint32
get_color(int idx)
{
    if(idx == 0) return COLOR_XY_AXIS;

    int counter = 0;
    while(idx % 10 == 0)
    {
        counter++;
        idx /= 10;
    }

    return counter < color_lines_size ? color_lines[counter] : COLOR_DEFAULT;
}

void
Painter::draw_plaid_line(int p) const
{
    static Point line; // 世界坐标

    static Vector2 view_L_T;
    static Vector2 view_R_B;

    static float unit_size = 0;

    if(p < 0) return;

    p = pow(10, p);

    view_L_T = painter_view->Get_view_left_top_position();
    view_R_B = painter_view->Get_view_right_bottom_position();

    unit_size = painter_view->Get_unit_size();

    line = (Point)view_L_T;

    line.px = (line.px / p) * p;
    line.py = (line.py / p) * p;

    for(; line.px <= view_R_B.vx; line.px += p)
    {
        lineColor(
            renderer,
            (line.px - view_L_T.vx) * unit_size,
            0,
            (line.px - view_L_T.vx) * unit_size,
            (view_R_B.vy - view_L_T.vy) * unit_size,
            get_color(line.px)

        );
    }

    for(; line.py <= view_R_B.vy; line.py += p)
    {
        lineColor(
            renderer,
            0,
            (line.py - view_L_T.vy) * unit_size,
            (view_R_B.vx - view_L_T.vx) * unit_size,
            (line.py - view_L_T.vy) * unit_size,
            get_color(line.py)

        );
    }
}

void
Painter::Draw_plaid() const
{
    float unit_size = painter_view->Get_unit_size();

    int level = -1;

    if(unit_size >= 5)
        level = 0;
    else if(unit_size >= 1e-1) // 0.1
        level = 2;
    else if(unit_size >= 5e-3) // 0.005
        level = 3;
    else if(unit_size >= 1e-3) // 0.001
        level = 5;
    else if(unit_size >= 5e-5) // 0.00005
        level = 6;
    else if(unit_size >= 1e-5) // 0.00001
        level = 8;
    else
        level = 9;

    draw_plaid_line(level);
}
