
// tools.h

#pragma once

#include "base.h"

#include <string>
#include <unordered_map>

// 定时器
class Timer
{
public:
    Timer()  = default;
    ~Timer() = default;

public:
    void On_update(float dt);
    void Restart(float t = 0);
    void Shot(); // 立即触发

public:
    bool is_paused   = false; // 计时器是否暂停
    bool is_one_shot = false; // 计时器是否为一次性触发

    void Set_wait_time(float t) { t > 0.0f ? wait_time = t : wait_time = 0.0f; }
    void Set_wait_time_add(float t) { t > 0.0f ? wait_time += t : wait_time = 0.0f; }
    void Set_wait_time_mul(float t) { t > 0.0f ? wait_time *= t : wait_time = 0.0f; }
    void Set_on_timeout(Callback f) { on_timeout = f; }

    const float& Get_pass_time() const { return pass_time; }
    const bool&  Get_is_shotted() const { return is_shotted; }

private:
    float pass_time  = 0;     // 计时器已经过去的时间
    float wait_time  = 0;     // 计时器等待的时间
    bool  is_shotted = false; // 计时器是否已经触发过一次

    Callback on_timeout = nullptr; // 超时回调函数
};


// 最基础的图形类，用四个字节的数组表示一个矩阵，每个字节表示一个像素点的颜色
class Shape
{
public:
    Shape() = default;
    ~Shape(); // **记得释放内存**

public:
    // 重新设置形状
    void Shape_reset(int = 0, int = 0, int = 0);
    void Shape_reset(const int*, int, int);

    // 合并两个形状
    void Shape_merge(Shape*, std::function<void(int&, int&)> f, int dx = 0, int dy = 0);

    // 获取形状的宽高、缓冲区大小
    int Shape_wide() const;
    int Shape_high() const;
    int Shape_long() const;

    int* Shape_buffer() const;

    // 获取形状某个点的值
    int Shape_in(int) const;
    int Shape_in(int, int) const;

    // 绘制圆形
    void Shape_draw_point(int, int, int = 0);
    void Shape_draw_line(int, int, int, int, int = 0);
    void Shape_draw_rectangle(int, int, int, int, int = 0);
    void Shape_draw_circle(int, int, int, int = 0);

    // 复制形状
    void Shape_copy(Shape*);
    // 设置所有单位的值
    void Shape_clear(int = 0);

protected:
    int* shape_buffer = nullptr;
    int  shape_wide   = 0;
    int  shape_high   = 0;
    int  shape_long   = 0;
};


// Object
class Object
{
public:
    Object() = default;
    Object(const Vector2& pos, const Vector2& vel = VECTOR2_ZERO, float mass = 0, const Color& color = COLOR_BLACK);
    Object(float radius, float mass, const Color& color);
    ~Object() = default;

public:
    virtual void On_update(float delta_time);
    virtual void On_render() const;

public:
    bool is_use_friction       = false;
    bool is_use_air_resistance = false;

    void Force(const Vector2& force);
    void Move(const Vector2& move);
    void Move_to(const Vector2& dst);
    void Move_to_x(float dst_x);
    void Move_to_y(float dst_y);

    void Stop_move();
    void Stop_move_x();
    void Stop_move_y();

    const Vector2& Get_position() const;
    const Vector2& Get_velocity() const;
    const Vector2& Get_acceleration() const;
    float          Get_mass() const;
    float          Get_radius() const;
    const Color&   Get_color() const;

    void Set_position(const Vector2& position);
    void Set_velocity(const Vector2& velocity);
    void Set_acceleration(const Vector2& acceleration);
    void Set_mass(float mass);
    void Set_radius(float radius);
    void Set_color(const Color& color);

    void Set_friction(float friction);
    void Set_air_resistance(float resistance);

protected:
    float movement_friction       = 0.0f;
    float movement_air_resistance = 0.0f;

    Vector2 movement_position;     // 位置
    Vector2 movement_velocity;     // 速度
    Vector2 movement_acceleration; // 加速度
    float   movement_mass = 0;     // 质量（为0时视为质量无穷大）
    float   object_radius = 0;     // 半径
    Color   object_color;          // 颜色

    Vector2 acceleration_last_frame; // 上一帧的加速度
};

#define STATE_NULL "state_null"

class StateNode
{
public:
    StateNode(const char* id);
    ~StateNode() = default;

    virtual void On_enter() {}
    virtual void On_render() const {}
    virtual void On_update(float delta_time) {}
    virtual void On_update_after(float delta_time) {}
    virtual void On_exit() {}

    const char* const state_id;
};

typedef std::unordered_map<std::string, StateNode*> StatePool;

class StateMachine
{
public:
    StateMachine();
    ~StateMachine();

    void On_render() const { current_state->On_render(); }
    void On_update(float delta_time) { current_state->On_update(delta_time); }
    void On_update_after(float delta_time) { current_state->On_update_after(delta_time); }

    void Switch_to_state(const char* id);       // 切换状态
    void Register_state(StateNode* state_node); // 注册状态
    void Clear_states();                        // 清空状态机

    const char* Current_state() const { return current_state->state_id; }

private:
    StateNode* current_state = nullptr; // 当前状态
    StatePool  state_pool;              // 状态池
};
