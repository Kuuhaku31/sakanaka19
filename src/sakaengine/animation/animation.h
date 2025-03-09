
// animation.h

#pragma once

#include "sakaengine.h"


// 动画信息
struct AnimationInformation
{
    // 必须设置的参数
    sakaengine::Texture* texture = nullptr; // 纹理

    uint16_t  num_x          = 0;       // 纹理横向切成多少帧
    uint16_t  num_y          = 0;       // 纹理纵向切成多少帧
    uint16_t* frame_idx_list = nullptr; // 帧索引列表
    uint16_t  frame_count    = 0;       // 帧数

    // 可选参数
    float frame_interval = 0.0f;  // 帧间隔
    float angle          = 0.0f;  // 渲染角度
    float texture_size   = 0.0f;  // 渲染大小，对于这个纹理，一个单位长度等于 texture_size 个像素
    bool  is_loop        = false; // 是否循环播放

    CorrectivePos on_corrective = nullptr; // 位置修正
};


// 动画模板
class AnimationTemplate
{
    friend class AnimationInstance;

public:
    AnimationTemplate(const AnimationInformation& info);
    ~AnimationTemplate();

private:
    sakaengine::Texture* texture = nullptr; // 纹理

    Point*   frame_src_list = nullptr; // 帧源列表
    uint16_t frame_w        = 0;       // 帧宽
    uint16_t frame_h        = 0;       // 帧高
    uint16_t frame_count    = 0;       // 帧数

    float frame_interval = 0.1f;  // 帧间隔
    float angle          = 0.0f;  // 渲染角度
    float texture_size   = 1.0f;  // 渲染大小，对于这个纹理，一个单位长度等于 texture_size 个像素
    bool  is_loop        = false; // 是否循环播放

    CorrectivePos on_corrective; // 位置修正
};


// 动画实例
class AnimationInstance : public Vector2
{
public:
    AnimationInstance(const AnimationTemplate& animation, Callback f = nullptr);
    ~AnimationInstance() = default;

    void On_render() const;           // 渲染
    void On_update(float delta_time); // 更新

    void Restart();              // 重置
    void Set_play_time(float t); // 设置播放时间

    void Set_frame_interval(float interval);
    void Set_frame_interval_add(float interval);
    void Set_frame_interval_mul(float interval);
    void Set_size(float size);
    void Set_size_add(float size);
    void Set_size_mul(float size);


    void
    Set_on_corrective(CorrectivePos f)
    {
        on_corrective = f;
    }
    void
    Set_on_finished(Callback f)
    {
        on_finished = f;
    }

    const float&
    Get_ph_w() const
    {
        return ph_w;
    } // 物理宽
    const float&
    Get_ph_h() const
    {
        return ph_h;
    } // 物理高
    const bool&
    Is_finished() const
    {
        return is_finished;
    } // 动画是否结束


    bool  is_paused = false; // 动画是否暂停
    float angle     = 0.0f;  // 渲染角度


private:
    const AnimationTemplate& animation;

    float texture_size = 0.0f; // 渲染大小
    float ph_w         = 0.0f; // 物理宽
    float ph_h         = 0.0f; // 物理高

    CorrectivePos on_corrective = nullptr; // 位置修正


    uint16_t frame_current = 0;     // 当前帧
    bool     is_finished   = false; // 动画是否结束

    float frame_pass_time = 0; // 当前帧已经过去的时间
    float frame_interval  = 0; // 帧间隔

    Callback on_finished; // 动画结束回调


    inline void
    update_ph_vy()
    {
        ph_w = animation.frame_w / texture_size;
        ph_h = animation.frame_h / texture_size;
    }
};
