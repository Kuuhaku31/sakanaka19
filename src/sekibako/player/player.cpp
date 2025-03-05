
// player.cpp

#include "player.h"
#include "player_states.h"

#include "animation.h"


Player::Player()
    : Object(10.0f, 1.0f, COLOR_RED)
{
    // 注册状态
    Register_state(new PlayerStatesIdle(*this));
    Register_state(new PlayerStatesWalk(*this));
    Register_state(new PlayerStatesRun(*this));
    Register_state(new PlayerStatesLeviate(*this));
    Register_state(new PlayerStatesJump(*this));
    Register_state(new PlayerStatesRoll(*this));
    Register_state(new PlayerStatesDash(*this));
    Register_state(new PlayerStatesAttack(*this));

    Switch_to_state(PLAYER_STATE_IDLE);

    // 计时器
    roll_cd_timer.is_one_shot = true;
    roll_cd_timer.Set_on_timeout([&]() { roll_cd_done = true; }); // 翻滚冷却计时结束

    attack_cd_timer.is_one_shot = true;
    attack_cd_timer.Set_on_timeout([&]() { attack_cd_done = true; }); // 攻击冷却计时结束
}

Player::~Player()
{
    Clear_states();
}

void
Player::On_render() const
{
    static const Painter& painter = Painter::Instance();

    painter.DrawCircle(
        movement_position.vx,
        movement_position.vy,
        object_radius,
        object_color,
        true

    );

    switch(facing_dir)
    {
    case Facing_Dir::Left:
        painter.DrawLine(
            movement_position.vx,
            movement_position.vy,
            movement_position.vx - 1,
            movement_position.vy,
            COLOR_YELLOW);
        break;

    case Facing_Dir::Right:
        painter.DrawLine(
            movement_position.vx,
            movement_position.vy,
            movement_position.vx + 1,
            movement_position.vy,
            COLOR_YELLOW);
        break;
    }

    StateMachine::On_render();
}

void
Player::On_update(float delta_time)
{
    // 地面修正 y 坐标
    floor_correct_y = floor_y - object_radius;

    // 重置跳跃次数
    if(is_on_ground) can_jump_count = can_jump_count_max;

    // 更新角色加速度
    movement_acceleration += get_try_move_dir() * current_move_acceleration;

    // 更新角色朝向
    // 要求朝向没有被锁定并且尝试朝一个方向移动
    if(!is_Lock_facing_dir && is_try_move_x_on_one_dir())
    {
        if(CONTROLER_GET(player_controler, PLAYER_CONTROL_PRESS_LEFT))
        {
            facing_dir = Facing_Dir::Left;
        }
        else if(CONTROLER_GET(player_controler, PLAYER_CONTROL_PRESS_RIGHT))
        {
            facing_dir = Facing_Dir::Right;
        }
    }

    // 更新动作朝向
    if(!is_lock_action_dir)
    {
        if(CONTROLER_GET(player_controler, PLAYER_CONTROL_PRESS_ARROW_UP))
        {
            action_dir = Action_Dir::Up;
        }
        else if(CONTROLER_GET(player_controler, PLAYER_CONTROL_PRESS_ARROW_DOWN))
        {
            action_dir = Action_Dir::Down;
        }
        else if(CONTROLER_GET(player_controler, PLAYER_CONTROL_PRESS_ARROW_LEFT))
        {
            action_dir = Action_Dir::Left;
        }
        else if(CONTROLER_GET(player_controler, PLAYER_CONTROL_PRESS_ARROW_RIGHT))
        {
            action_dir = Action_Dir::Right;
        }
    }

    // 更新状态机
    StateMachine::On_update(delta_time);

    // 计算重力
    if(enable_gravity) movement_acceleration.vy += GRAVITY;

    // 更新物理
    Object::On_update(delta_time);

    // 修正位置
    if(movement_position.vy > floor_correct_y) movement_velocity.vy = movement_position.vy = floor_correct_y;

    // 更新状态机
    StateMachine::On_update_after(delta_time);

    // 更新计时器
    roll_cd_timer.On_update(delta_time);
    attack_cd_timer.On_update(delta_time);
}

// 角色是否至少按下一个水平移动键
bool
Player::is_try_move_x() const
{
    return player_controler & PLAYER_CONTROL_IS_MOVE_X;
}

// 角色是否只按下一个水平移动键
bool
Player::is_try_move_x_on_one_dir() const
{
    return bool(player_controler & PLAYER_CONTROL_PRESS_LEFT) ^ bool(player_controler & PLAYER_CONTROL_PRESS_RIGHT);
}

// 角色面朝方向是否背对速度
bool
Player::is_back_to_velocity() const
{
    switch(facing_dir)
    {
    case Facing_Dir::Left: return movement_velocity.vx > 0;
    case Facing_Dir::Right: return movement_velocity.vx < 0;
    default: return false;
    }
}

// 获取角色尝试移动的方向
const Vector2&
Player::get_try_move_dir() const
{
    static Vector2 move_dir;

    move_dir.to_zero();
    if(player_controler & PLAYER_CONTROL_PRESS_LEFT) move_dir += VECTOR2_UNIT_LEFT;
    if(player_controler & PLAYER_CONTROL_PRESS_RIGHT) move_dir += VECTOR2_UNIT_RIGHT;
    move_dir.to_unit();

    return move_dir;
}

bool
Player::is_try_walk() const
{
    return is_try_move_x_on_one_dir() && CONTROLER_GET(player_controler, PLAYER_CONTROL_PRESS_L_ALT);
}

bool
Player::is_try_run() const
{
    return is_try_move_x_on_one_dir() && !CONTROLER_GET(player_controler, PLAYER_CONTROL_PRESS_L_ALT);
}

// 获取角色面朝方向
const Vector2&
Player::get_facing_vector() const
{
    static Vector2 facing_vector;
    switch(facing_dir)
    {
    case Facing_Dir::Left: facing_vector = VECTOR2_UNIT_LEFT; break;
    case Facing_Dir::Right: facing_vector = VECTOR2_UNIT_RIGHT; break;
    default: facing_vector = VECTOR2_UNIT_RIGHT; break;
    }
    return facing_vector;
}
