
// animation.cpp

#include "animation.h"
#include "utils.h"


// 动画模板
AnimationTemplate::AnimationTemplate(const AnimationInformation& info)
{
    // 必须设置的参数
    texture      = info.texture;
    texture_size = info.texture_size;

    int tex_w = 0, tex_h = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &tex_w, &tex_h); // 获取纹理的宽高

    frame_w     = tex_w / info.num_x;
    frame_h     = tex_h / info.num_y;
    frame_count = info.frame_count;

    frame_src_list = new Point[frame_count];
    for(uint16_t i = 0; i < frame_count; i++)
    {
        uint16_t idx = info.frame_idx_list[i];

        Point& frame_src = frame_src_list[i];

        frame_src.px = (idx % info.num_x) * frame_w;
        frame_src.py = (idx / info.num_x) * frame_h;
    }

    // 可选参数
    if(info.frame_interval > 0) frame_interval = info.frame_interval;
    angle = info.angle;
    if(info.texture_size > 0) texture_size = info.texture_size;
    is_loop       = info.is_loop;
    on_corrective = info.on_corrective;
}


AnimationTemplate::~AnimationTemplate()
{
    delete[] frame_src_list;
}


// 动画实例
AnimationInstance::AnimationInstance(const AnimationTemplate& animation, Callback animation_finished_callback)
    : animation(animation)
{
    frame_interval = animation.frame_interval; // 帧间隔

    angle         = animation.angle;           // 渲染角度
    on_corrective = animation.on_corrective;   // 位置修正

    texture_size = animation.texture_size;
    ph_w         = animation.frame_w / texture_size; // w 表示纹理单位长度 = 纹理像素长度 / texture_size
    ph_h         = animation.frame_h / texture_size; // h 表示纹理单位长度 = 纹理像素长度 / texture_size

    on_finished = animation_finished_callback;       // 动画结束回调
}


void
AnimationInstance::On_render() const
{
    static IRect src_rect;
    static FRect dst_rect;

    src_rect.x = animation.frame_src_list[frame_current].px;
    src_rect.y = animation.frame_src_list[frame_current].py;
    src_rect.w = animation.frame_w;
    src_rect.h = animation.frame_h;

    dst_rect.x = vx;
    dst_rect.y = vy;
    dst_rect.w = ph_w;
    dst_rect.h = ph_h;
    if(on_corrective) on_corrective(dst_rect.x, dst_rect.y, ph_w, ph_h);

    sakaengine::DrawTexture(animation.texture, src_rect, dst_rect, angle);
}


void
AnimationInstance::On_update(float delta_time)
{
    // 如果动画暂停，则不更新
    if(is_paused) return;

    // 更新计时器
    frame_pass_time += delta_time;

    // 如果计时器超时
    if(frame_pass_time >= frame_interval)
    {
        frame_pass_time -= frame_interval;

        frame_current++;
        if(frame_current >= animation.frame_count) // 如果超出帧数
        {
            if(animation.is_loop)                  // 如果是循环播放
            {
                frame_current = 0;
            }
            else                      // 如果不是循环播放
            {
                is_paused     = true; // 暂停动画
                is_finished   = true; // 动画结束
                frame_current = animation.frame_count - 1;
                if(on_finished) on_finished();
            }
        }
    }
}


void
AnimationInstance::Restart()
{
    is_finished   = false;
    frame_current = 0;

    frame_pass_time = 0;
}


void
AnimationInstance::Set_play_time(float t)
{
    if(t < 0) t = 0;
    frame_interval = t / animation.frame_count;
}


void
AnimationInstance::Set_frame_interval(float interval)
{
    if(interval < 0) interval = 0;
    frame_interval = interval;
}


void
AnimationInstance::Set_frame_interval_add(float interval)
{
    frame_interval += interval;
    if(frame_interval < 0) frame_interval = 0;
}


void
AnimationInstance::Set_frame_interval_mul(float interval)
{
    frame_interval *= interval;
    if(frame_interval < 0) frame_interval = 0;
}


void
AnimationInstance::Set_size(float size)
{
    if(size > 0)
    {
        texture_size = size;
        update_ph_vy();
    }
}


void
AnimationInstance::Set_size_add(float size)
{
    if(texture_size + size > 0)
    {
        texture_size += size;
        update_ph_vy();
    }
}


void
AnimationInstance::Set_size_mul(float size)
{
    if(size > 0)
    {
        texture_size *= size;
        update_ph_vy();
    }
}
