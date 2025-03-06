
#pragma once

#include <stdio.h>

namespace game
{

void Initialize();

void Play();

void Shutdown();

bool GetIsInitialized();

} // namespace game


class Singleton
{
private:
    Singleton() { printf("Singleton Constructor\n"); }
    Singleton(const Singleton&)            = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton&
    getInstance()
    {
        static Singleton instance; // 局部静态变量，C++11 线程安全
        return instance;
    }

    void
    show()
    {
        printf("Singleton Instance\n");
    }
};