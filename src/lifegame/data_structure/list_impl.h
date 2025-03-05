
// list_impl.h

#pragma once

#include "list.h"


// 构造函数定义
template<typename Tem>
inline List<Tem>::List(Compare less, Compare equal)
    : less(less)
    , equal(equal)
{
}

// 析构函数定义
template<typename Tem>
List<Tem>::~List()
{
    ListNode<Tem>* temp = nullptr;
    while(head)
    {
        temp = head;
        head = head->next;
        delete temp->data;
        delete temp;
    }
}


template<typename Tem>
template<typename... Args>
inline void
List<Tem>::Insert(Args&&... args) // 保证从小到大排序，二分查找
{
    ListNode<Tem>* node = new ListNode<Tem>();
    node->data          = new Tem(std::forward<Args>(args)...);

    // 查找，若相等则覆盖
    ListNode<Tem>* temp = head;
    while(temp)
    {
        if(less(*node->data, *temp->data))
        {
            if(temp->prev)
            {
                temp->prev->next = node;
                node->prev       = temp->prev;
            }
            else
            {
                head = node;
            }
            node->next = temp;
            temp->prev = node;
            size++;
            return;
        }
        else if(equal(*node->data, *temp->data))
        {
            delete temp->data;
            temp->data = node->data;
            delete node;
            return;
        }
        temp = temp->next;
    }
}

template<typename Tem>
inline Tem*
List<Tem>::Pop_back()
{
    if(size == 0)
    {
        return nullptr;
    }

    ListNode<Tem>* temp = tail;
    Tem*           data = temp->data;

    if(size == 1)
    {
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        tail       = tail->prev;
        tail->next = nullptr;
    }

    delete temp;
    size--;

    return data;
}

template<typename Tem>
inline Tem*
List<Tem>::Pop_front()
{
    if(size == 0)
    {
        return nullptr;
    }

    ListNode<Tem>* temp = head;
    Tem*           data = temp->data;

    if(size == 1)
    {
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        head       = head->next;
        head->prev = nullptr;
    }

    delete temp;
    size--;

    return data;
}
