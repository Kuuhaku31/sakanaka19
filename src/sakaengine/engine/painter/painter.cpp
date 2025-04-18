
// painter.cpp

#include "sakaengine.h"

#include "shared.h"


// 绘制图形

void
sakaengine::DrawLine(float A, float B, float C, const Color& color)
{

    static float start_x, start_y, end_x, end_y     = 0.0f;
    static float view_y1, view_y2, view_x1, view_x2 = 0.0f;
    static float unit_size = 0.0f;


    if(!painter_view) return;

    view_y1 = painter_view->Get_view_left_top_position().vy;
    view_y2 = painter_view->Get_view_right_bottom_position().vy;
    view_x1 = painter_view->Get_view_left_top_position().vx;
    view_x2 = painter_view->Get_view_right_bottom_position().vx;

    unit_size = painter_view->Get_unit_size();

    if(!A) // y = -C / B
    {
        start_y = -C / B;
        if(start_y < view_y1 || start_y > view_y2) return;

        start_x = view_x1;
        end_x   = view_x2;
        end_y   = start_y;
    }
    else if(!B) // x = -C / A
    {
        start_x = -C / A;
        if(start_x < view_x1 || start_x > view_x2) return;

        start_y = view_y1;
        end_y   = view_y2;
        end_x   = start_x;
    }
    else
    {
        start_x = view_x1;
        end_x   = view_x2;

        start_y = (-A * start_x - C) / B;
        if(start_y < view_y1)
        {
            start_y = view_y1;
            start_x = (-B * start_y - C) / A;
            if(start_x < view_x1 || start_x > view_x2) return;
        }
        else if(start_y > view_y2)
        {
            start_y = view_y2;
            start_x = (-B * start_y - C) / A;
            if(start_x < view_x1 || start_x > view_x2) return;
        }

        end_y = (-A * end_x - C) / B;
        if(end_y < view_y1)
        {
            end_y = view_y1;
            end_x = (-B * end_y - C) / A;
            if(end_x < view_x1 || end_x > view_x2) return;
        }
        else if(end_y > view_y2)
        {
            end_y = view_y2;
            end_x = (-B * end_y - C) / A;
            if(end_x < view_x1 || end_x > view_x2) return;
        }
    }

    lineRGBA(
        sdl_renderer,
        (start_x - view_x1) * unit_size,
        (start_y - view_y1) * unit_size,
        (end_x - view_x1) * unit_size,
        (end_y - view_y1) * unit_size,
        color.r,
        color.g,
        color.b,
        color.a

    );
}


void
sakaengine::DrawLine(Vector2 start, Vector2 end, const Color& color)
{
    static float start_x, start_y, end_x, end_y     = 0.0f;
    static float view_y1, view_y2, view_x1, view_x2 = 0.0f;
    static float unit_size = 0.0f;

    if(!painter_view) return;

    view_y1 = painter_view->Get_view_left_top_position().vy;
    view_y2 = painter_view->Get_view_right_bottom_position().vy;
    view_x1 = painter_view->Get_view_left_top_position().vx;
    view_x2 = painter_view->Get_view_right_bottom_position().vx;

    unit_size = painter_view->Get_unit_size();

    if(start.vx > end.vx) // 确保 start_x < end_x
    {
        swap<float>(start.vx, end.vx);
        swap<float>(start.vy, end.vy);
    }

    float A = end.vy - start.vy;
    float B = start.vx - end.vx;
    float C = -B * start.vy - A * start.vx;

    if(!A) // y = -C / B
    {
        start_y = -C / B;
        if(start_y < view_y1 || start_y > view_y2) return;
        if(end.vx < view_x1 || start.vx > view_x2) return;

        start_x = start.vx < view_x1 ? view_x1 : start.vx;
        end_x   = end.vx > view_x2 ? view_x2 : end.vx;

        end_y = start_y;
    }
    else if(!B) // x = -C / A
    {
        start_x = -C / A;
        if(start_x < view_x1 || start_x > view_x2) return;
        if(start.vy > end.vy) swap<float>(start.vy, end.vy);
        if(end.vy < view_y1 || start.vy > view_y2) return;

        start_y = start.vy < view_y1 ? view_y1 : start.vy;
        end_y   = end.vy > view_y2 ? view_y2 : end.vy;

        end_x = start_x;
    }
    else
    {
        if(end.vx < view_x1 || start.vx > view_x2) return;

        start_x = start.vx < view_x1 ? view_x1 : start.vx;
        end_x   = end.vx > view_x2 ? view_x2 : end.vx;

        start_y = (-A * start_x - C) / B;
        if(start_y < view_y1)
        {
            start_y = view_y1;
            start_x = (-B * start_y - C) / A;
            if(start_x < view_x1 || start_x > view_x2) return;
        }
        else if(start_y > view_y2)
        {
            start_y = view_y2;
            start_x = (-B * start_y - C) / A;
            if(start_x < view_x1 || start_x > view_x2) return;
        }

        end_y = (-A * end_x - C) / B;
        if(end_y < view_y1)
        {
            end_y = view_y1;
            end_x = (-B * end_y - C) / A;
            if(end_x < view_x1 || end_x > view_x2) return;
        }
        else if(end_y > view_y2)
        {
            end_y = view_y2;
            end_x = (-B * end_y - C) / A;
            if(end_x < view_x1 || end_x > view_x2) return;
        }
    }

    lineRGBA(
        sdl_renderer,
        (start_x - view_x1) * unit_size,
        (start_y - view_y1) * unit_size,
        (end_x - view_x1) * unit_size,
        (end_y - view_y1) * unit_size,
        color.r,
        color.g,
        color.b,
        color.a

    );
}


void
sakaengine::DrawArc(const Vector2& center, float radius, float start_angle, float end_angle, const Color& color)
{
    if(!painter_view) return;

    float view_left_top_position_x = painter_view->Get_view_left_top_position().vx;
    float view_left_top_position_y = painter_view->Get_view_left_top_position().vy;

    float unit_size = painter_view->Get_unit_size();

    arcRGBA(
        sdl_renderer,
        (center.vx - view_left_top_position_x) * unit_size,
        (center.vy - view_left_top_position_y) * unit_size,
        radius * unit_size,
        start_angle,
        end_angle,
        color.r,
        color.g,
        color.b,
        color.a

    );
}


inline void
DrawPartialCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int screenWidth, int screenHeight)
{
    int x   = radius;
    int y   = 0;
    int err = 0;

    while(x >= y)
    {
        // 绘制八个对称点，只绘制在画布范围内的点
        if(centerX + x >= 0 && centerX + x < screenWidth && centerY + y >= 0 && centerY + y < screenHeight) pixelRGBA(renderer, centerX + x, centerY + y, r, g, b, a);
        if(centerX + y >= 0 && centerX + y < screenWidth && centerY + x >= 0 && centerY + x < screenHeight) pixelRGBA(renderer, centerX + y, centerY + x, r, g, b, a);
        if(centerX - y >= 0 && centerX - y < screenWidth && centerY + x >= 0 && centerY + x < screenHeight) pixelRGBA(renderer, centerX - y, centerY + x, r, g, b, a);
        if(centerX - x >= 0 && centerX - x < screenWidth && centerY + y >= 0 && centerY + y < screenHeight) pixelRGBA(renderer, centerX - x, centerY + y, r, g, b, a);
        if(centerX - x >= 0 && centerX - x < screenWidth && centerY - y >= 0 && centerY - y < screenHeight) pixelRGBA(renderer, centerX - x, centerY - y, r, g, b, a);
        if(centerX - y >= 0 && centerX - y < screenWidth && centerY - x >= 0 && centerY - x < screenHeight) pixelRGBA(renderer, centerX - y, centerY - x, r, g, b, a);
        if(centerX + y >= 0 && centerX + y < screenWidth && centerY - x >= 0 && centerY - x < screenHeight) pixelRGBA(renderer, centerX + y, centerY - x, r, g, b, a);
        if(centerX + x >= 0 && centerX + x < screenWidth && centerY - y >= 0 && centerY - y < screenHeight) pixelRGBA(renderer, centerX + x, centerY - y, r, g, b, a);

        if(err <= 0) // 计算下一个点
        {
            y   += 1;
            err += 2 * y + 1;
        }
        if(err > 0)
        {
            x   -= 1;
            err -= 2 * x + 1;
        }
    }
}


void
sakaengine::DrawCircle(const Vector2& center, float radius, const Color& color, bool is_solid)
{
    if(!painter_view) return;

    float view_left_top_position_x = painter_view->Get_view_left_top_position().vx;
    float view_left_top_position_y = painter_view->Get_view_left_top_position().vy;

    float unit_size = painter_view->Get_unit_size();


    if(is_solid)
    {
        float dx = center.vx - painter_view->Get_view_center_position().vx;
        float dy = center.vy - painter_view->Get_view_center_position().vy;

        float h_wide = painter_view->Get_view_size_half().vx;
        float h_high = painter_view->Get_view_size_half().vy;

        if(dx < 0) dx = -dx;
        if(dy < 0) dy = -dy;

        float u_x = dx - h_wide;
        float u_y = dy - h_high;

        if(u_x < 0) u_x = 0;
        if(u_y < 0) u_y = 0;

        if(u_x * u_x + u_y * u_y >= radius * radius)
        {
            DrawPartialCircle(
                sdl_renderer,
                (center.vx - view_left_top_position_x) * unit_size,
                (center.vy - view_left_top_position_y) * unit_size,
                radius * unit_size,
                color.r,
                color.g,
                color.b,
                color.a,
                painter_view->Get_view_size().vx * unit_size,
                painter_view->Get_view_size().vy * unit_size

            );
            return;
        }

        if(painter_view->Get_view_size().module() / radius > 0.07)
        {
            DrawPartialCircle(
                sdl_renderer,
                (center.vx - view_left_top_position_x) * unit_size,
                (center.vy - view_left_top_position_y) * unit_size,
                radius * unit_size,
                color.r,
                color.g,
                color.b,
                color.a,
                painter_view->Get_view_size().vx * unit_size,
                painter_view->Get_view_size().vy * unit_size

            );
        }
        else
        {
            Vector2 dir = painter_view->Get_view_center_position() - Vector2{ center.vx, center.vy };

            dir.to_unit();
            dir *= radius;

            DrawLine(
                dir.vx,
                dir.vy,
                -radius * radius - center.vx * (dir.vx - center.vx) - center.vy * (dir.vy - center.vy),
                color

            );
        }
    }
    else
    {
        filledCircleRGBA(
            sdl_renderer,
            (center.vx - view_left_top_position_x) * unit_size,
            (center.vy - view_left_top_position_y) * unit_size,
            radius * unit_size,
            color.r,
            color.g,
            color.b,
            color.a

        );
    }
}


void
sakaengine::DrawRect(const FRect& rect, const Color& color, bool is_solid)
{
    if(!painter_view) return;

    float view_left_top_position_x = painter_view->Get_view_left_top_position().vx;
    float view_left_top_position_y = painter_view->Get_view_left_top_position().vy;

    float unit_size = painter_view->Get_unit_size();

    if(is_solid)
    {
        sakaengine::DrawLine({ rect.x, rect.y }, { rect.x + rect.w, rect.y }, color);
        sakaengine::DrawLine({ rect.x + rect.w, rect.y }, { rect.x + rect.w, rect.y + rect.h }, color);
        sakaengine::DrawLine({ rect.x + rect.w, rect.y + rect.h }, { rect.x, rect.y + rect.h }, color);
        sakaengine::DrawLine({ rect.x, rect.y + rect.h }, { rect.x, rect.y }, color);
    }
    else
    {
        // 使用 SDL2_gfx 绘制填充矩形
        boxRGBA(
            sdl_renderer,
            (rect.x - view_left_top_position_x) * unit_size,
            (rect.y - view_left_top_position_y) * unit_size,
            (rect.x + rect.w - view_left_top_position_x) * unit_size,
            (rect.y + rect.h - view_left_top_position_y) * unit_size,
            color.r,
            color.g,
            color.b,
            color.a

        );
    }
}


void
sakaengine::DrawTriangle(const Vector2& a, const Vector2& b, const Vector2& c, const Color& color, bool is_solid)
{
    if(!painter_view) return;

    float view_left_top_position_x = painter_view->Get_view_left_top_position().vx;
    float view_left_top_position_y = painter_view->Get_view_left_top_position().vy;

    float unit_size = painter_view->Get_unit_size();

    if(is_solid)
    {
        aatrigonRGBA(
            sdl_renderer,
            (a.vx - view_left_top_position_x) * unit_size,
            (a.vy - view_left_top_position_y) * unit_size,
            (b.vx - view_left_top_position_x) * unit_size,
            (b.vy - view_left_top_position_y) * unit_size,
            (c.vx - view_left_top_position_x) * unit_size,
            (c.vy - view_left_top_position_y) * unit_size,
            color.r,
            color.g,
            color.b,
            color.a

        );
    }
    else
    {
        filledTrigonRGBA(
            sdl_renderer,
            (a.vx - view_left_top_position_x) * unit_size,
            (a.vy - view_left_top_position_y) * unit_size,
            (b.vx - view_left_top_position_x) * unit_size,
            (b.vy - view_left_top_position_y) * unit_size,
            (c.vx - view_left_top_position_x) * unit_size,
            (c.vy - view_left_top_position_y) * unit_size,
            color.r,
            color.g,
            color.b,
            color.a

        );
    }
}


void
sakaengine::DrawTexture(Texture* texture, const IRect& rect_src, const FRect& rect_dst, float angle)
{
    if(!painter_view) return;

    float view_left_top_position_x = painter_view->Get_view_left_top_position().vx;
    float view_left_top_position_y = painter_view->Get_view_left_top_position().vy;

    float unit_size = painter_view->Get_unit_size();

    static SDL_Rect src;
    static SDL_Rect dst;

    src = { rect_src.x, rect_src.y, rect_src.w, rect_src.h };

    dst.x = (rect_dst.x - view_left_top_position_x) * unit_size;
    dst.y = (rect_dst.y - view_left_top_position_y) * unit_size;
    dst.w = rect_dst.w * unit_size;
    dst.h = rect_dst.h * unit_size;

    SDL_RenderCopyEx(
        sdl_renderer,
        texture,
        &src,
        &dst,
        angle,
        nullptr,
        SDL_FLIP_NONE

    );
}
