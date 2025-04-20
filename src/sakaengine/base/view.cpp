
// view.cpp

#include "base.h"

View::View(Size display_size, const FRect& rect)
{
    view_left   = rect.x;
    view_top    = rect.y;
    view_right  = rect.x + rect.w;
    view_bottom = rect.y + rect.h;

    view_center_x = (view_left + view_right) / 2.0f;
    view_center_y = (view_top + view_bottom) / 2.0f;

    view_size_w = rect.w;
    view_size_h = rect.h;
    view_half_w = view_size_w / 2.0f;
    view_half_h = view_size_h / 2.0f;

    display_w = display_size.w;
    display_h = display_size.h;

    unit_size = view_size_w / display_w;
}

void
View::MoveCenterTo(float x, float y)
{
    view_center_x = x;
    view_center_y = y;

    view_left   = view_center_x - view_half_w;
    view_top    = view_center_y - view_half_h;
    view_right  = view_center_x + view_half_w;
    view_bottom = view_center_y + view_half_h;
}

void
View::MoveBy(float dx, float dy)
{
    view_center_x += dx;
    view_center_y += dy;

    view_left   = view_center_x - view_half_w;
    view_top    = view_center_y - view_half_h;
    view_right  = view_center_x + view_half_w;
    view_bottom = view_center_y + view_half_h;
}

void
View::SetDisplaySize(Size display_size)
{
    static float ratioW = 0.0f;
    static float ratioH = 0.0f;

    ratioW = float(display_size.w) / float(display_w);
    ratioH = float(display_size.h) / float(display_h);

    view_size_w *= ratioW;
    view_size_h *= ratioH;
    view_half_w *= ratioW;
    view_half_h *= ratioH;

    view_left   = view_center_x - view_half_w;
    view_top    = view_center_y - view_half_h;
    view_right  = view_center_x + view_half_w;
    view_bottom = view_center_y + view_half_h;

    display_w = display_size.w;
    display_h = display_size.h;
}

void
View::SetW(float w)
{
    view_size_w = w;
    view_half_w = w / 2.0f;

    view_left  = view_center_x - view_half_w;
    view_right = view_center_x + view_half_w;
}

void
View::SetH(float h)
{
    view_size_h = h;
    view_half_h = h / 2.0f;

    view_top    = view_center_y - view_half_h;
    view_bottom = view_center_y + view_half_h;
}

void
View::SetUnitSize(float size)
{
    static float ratio = 0.0f;

    ratio = unit_size / size;

    view_size_w *= ratio;
    view_size_h *= ratio;
    view_half_w *= ratio;
    view_half_h *= ratio;

    view_left   = view_center_x - view_half_w;
    view_top    = view_center_y - view_half_h;
    view_right  = view_center_x + view_half_w;
    view_bottom = view_center_y + view_half_h;

    unit_size = size;
}
