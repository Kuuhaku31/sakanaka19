
// player_states.h

#pragma once

#include "tools.h"


class Player;
class CollisionBox;
class AnimationInstance;

// 角色状态
#define PLAYER_STATE_IDLE "player_idle"       // 角色空闲
#define PLAYER_STATE_WALK "player_walk"       // 角色行走
#define PLAYER_STATE_RUN "player_run"         // 角色奔跑
#define PLAYER_STATE_DASH "player_dash"       // 角色冲刺
#define PLAYER_STATE_JUMP "player_jump"       // 角色跳跃
#define PLAYER_STATE_ROLL "player_roll"       // 角色翻滚
#define PLAYER_STATE_ASCEND "player_ascend"   // 角色上升
#define PLAYER_STATE_LEVIATE "player_leviate" // 角色悬浮
#define PLAYER_STATE_FALL "player_fall"       // 角色下落
#define PLAYER_STATE_ATTACK "player_attack"   // 角色攻击
#define PLAYER_STATE_HURT "player_hurt"       // 角色受伤
#define PLAYER_STATE_DEAD "player_dead"       // 角色死亡

#define PLAYER_IDEEL_COLOR COLOR_PURPLE
#define PLAYER_WALK_COLOR COLOR_CYAN
#define PLAYER_RUN_COLOR COLOR_GREEN
#define PLAYER_DASH_COLOR COLOR_YELLOW
#define PLAYER_JUMP_COLOR COLOR_BLUE
#define PLAYER_ROLL_COLOR COLOR_RED
#define PLAYER_LEVIATE_COLOR COLOR_ORANGE
#define PLAYER_ATTACK_COLOR COLOR_WHITE

// 角色空闲
class PlayerStatesIdle : public StateNode
{
public:
    PlayerStatesIdle(Player& player);
    ~PlayerStatesIdle();

    void On_enter() override;
    void On_render() const override;
    void On_update(float delta_time) override;
    void On_update_after(float delta_time) override;
    void On_exit() override;

private:
    Player& player;

    AnimationInstance* player_idel;
};

// 角色行走
class PlayerStatesWalk : public StateNode
{
public:
    PlayerStatesWalk(Player& player);
    ~PlayerStatesWalk() = default;

    void On_enter() override;
    void On_update(float delta_time) override;
    void On_exit() override;

private:
    Player& player;
};

// 角色奔跑
class PlayerStatesRun : public StateNode
{
public:
    PlayerStatesRun(Player& player);
    ~PlayerStatesRun();

    void On_enter() override;
    void On_render() const override;
    void On_update(float delta_time) override;
    void On_update_after(float delta_time) override;
    void On_exit() override;

private:
    Player& player;

    AnimationInstance* player_run;
};

// 角色冲刺
class PlayerStatesDash : public StateNode
{
public:
    PlayerStatesDash(Player& player);
    ~PlayerStatesDash();

    void On_enter() override;
    void On_render() const override;
    void On_update(float delta_time) override;
    void On_update_after(float delta_time) override;
    void On_exit() override;

private:
    Player& player;

    AnimationInstance* player_dash;
};

// 角色跳跃
class PlayerStatesJump : public StateNode
{
public:
    PlayerStatesJump(Player& player);
    ~PlayerStatesJump();

    void On_enter() override;
    void On_render() const override;
    void On_update(float delta_time) override;
    void On_update_after(float delta_time) override;
    void On_exit() override;

private:
    Player& player;

    AnimationInstance* player_jump; // 跳跃动画
};

// 角色翻滚
class PlayerStatesRoll : public StateNode
{
public:
    PlayerStatesRoll(Player& player);
    ~PlayerStatesRoll() = default;

    void On_enter() override;
    void On_render() const override;
    void On_update(float delta_time) override;
    void On_update_after(float delta_time) override;
    void On_exit() override;

private:
    Player& player;
    Timer   roll_timer; // 翻滚计时器

    AnimationInstance* roll_effect = nullptr; // 翻滚效果
};

// 角色上升
class PlayerStatesAscend : public StateNode
{
public:
    PlayerStatesAscend(Player& player);
    ~PlayerStatesAscend() = default;

    void On_enter() override;
    void On_update(float delta_time) override;
    void On_exit() override;

private:
    Player& player;
};

// 角色悬浮
class PlayerStatesLeviate : public StateNode
{
public:
    PlayerStatesLeviate(Player& player);
    ~PlayerStatesLeviate();

    void On_enter() override;
    void On_render() const override;
    void On_update(float delta_time) override;
    void On_update_after(float delta_time) override;
    void On_exit() override;

private:
    Player& player;

    AnimationInstance* player_leviate; // 悬浮动画
};

// 角色下落
class PlayerStatesFall : public StateNode
{
public:
    PlayerStatesFall(Player& player);
    ~PlayerStatesFall() = default;

    void On_enter() override;
    void On_update(float delta_time) override;
    void On_exit() override;

private:
    Player& player;
};

// 角色攻击
class PlayerStatesAttack : public StateNode
{
public:
    PlayerStatesAttack(Player& player);
    ~PlayerStatesAttack();

    void On_enter() override;
    void On_render() const override;
    void On_update(float delta_time) override;
    void On_update_after(float delta_time) override;
    void On_exit() override;

private:
    Player& player;
    // Timer   attack_action_timer;      // 攻击动作计时器
    Timer attack_effect_wait_timer; // 攻击效果等待计时器
    Timer attack_effect_timer;      // 攻击效果计时器

    CollisionBox* attack_box = nullptr; // 攻击碰撞盒

    AnimationInstance* player_attack; // 攻击动画
};
