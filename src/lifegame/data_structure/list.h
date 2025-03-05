// list.h

#pragma once

#include <functional>
#include <utility>

template<typename Tem>
struct ListNode
{
    ListNode* prev = nullptr; // 前驱指针
    ListNode* next = nullptr; // 后继指针
    Tem*      data;
};

template<typename Tem>
class List
{
public:
    typedef std::function<bool(const Tem&, const Tem&)> Compare;

public:
    List(Compare less, Compare equal);
    ~List();

    template<typename... Args>
    void Insert(Args&&... args);

    Tem* Pop_back();
    Tem* Pop_front();

private:
    ListNode<Tem>* head = nullptr; // 头指针
    ListNode<Tem>* tail = nullptr; // 尾指针

    int size = 0; // 链表大小

    Compare less;
    Compare equal;
};

#include "list_impl.h"
