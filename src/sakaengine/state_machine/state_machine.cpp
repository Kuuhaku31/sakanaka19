
// state_machine.cpp

#include "state_machine.h"

StateNode::StateNode(const char* id)
    : state_id(id)
{
}

StateMachine::StateMachine()
{
    static StateNode empty_state(STATE_NULL);
    state_pool[empty_state.state_id] = &empty_state;

    current_state = &empty_state;
}

StateMachine::~StateMachine()
{
    Clear_states();
}

// 切换状态
void
StateMachine::Switch_to_state(const char* id)
{
    // 如果存在目标状态，切换状态
    if(state_pool[id])
    {
        current_state->On_exit();
        current_state = state_pool[id];
        current_state->On_enter();
    }
}

// 注册状态
void
StateMachine::Register_state(StateNode* state_node)
{
    state_pool[state_node->state_id] = state_node;
}

void
StateMachine::Clear_states()
{
    // 清空状态机
    for(auto it = state_pool.begin(); it != state_pool.end();)
    {
        if(it->second->state_id == STATE_NULL)
        {
            ++it;
            continue;
        }
        delete it->second;
        it = state_pool.erase(it);
    }
}
