
// view.cpp

#include "base.h"

View::View(const Vector2& center_pos, const Vector2& size, float unit_size)
{
    Set_view_center_position(center_pos);
    Set_view_size(size);
    Set_unit_size(unit_size);
}

void
View::MoveXto(float x)
{
    view_center_position.vx       = x;
    view_left_top_position.vx     = view_center_position.vx - view_size_half.vx;
    view_right_bottom_position.vx = view_center_position.vx + view_size_half.vx;
}

void
View::MoveYto(float y)
{
    view_center_position.vy       = y;
    view_left_top_position.vy     = view_center_position.vy - view_size_half.vy;
    view_right_bottom_position.vy = view_center_position.vy + view_size_half.vy;
}

void
View::MoveXby(float dx)
{
    view_center_position.vx       += dx;
    view_left_top_position.vx      = view_center_position.vx - view_size_half.vx;
    view_right_bottom_position.vx  = view_center_position.vx + view_size_half.vx;
}

void
View::MoveYby(float dy)
{
    view_center_position.vy       += dy;
    view_left_top_position.vy      = view_center_position.vy - view_size_half.vy;
    view_right_bottom_position.vy  = view_center_position.vy + view_size_half.vy;
}

void
View::Set_view_center_position(const Vector2& pos)
{
    view_center_position = pos;

    view_left_top_position     = view_center_position - view_size_half;
    view_right_bottom_position = view_center_position + view_size_half;
}

void
View::Set_view_size(const Vector2& size)
{
    view_size      = size;
    view_size_half = size / 2;

    view_left_top_position     = view_center_position - view_size_half;
    view_right_bottom_position = view_center_position + view_size_half;
}

void
View::Set_unit_size(float size)
{
    unit_size = size;
    if(unit_size <= 0) unit_size = 1.0f;
}

const Vector2&
View::Get_view_center_position() const
{
    return view_center_position;
}

const Vector2&
View::Get_view_size() const
{
    return view_size;
}

const Vector2&
View::Get_view_size_half() const
{
    return view_size_half;
}

const Vector2&
View::Get_view_left_top_position() const
{
    return view_left_top_position;
}

const Vector2&
View::Get_view_right_bottom_position() const
{
    return view_right_bottom_position;
}

const float&
View::Get_unit_size() const
{
    return unit_size;
}
