
// launcher.h

#pragma once

#include <cstdint>

// 启动器
class Launcher
{
public:
    int Run();

private:
    // 读取配置文件，返回版本号
    uint32_t ReadVersion(const char* file_path = nullptr);
};
