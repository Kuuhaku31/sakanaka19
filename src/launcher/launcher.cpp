
// launcher.cpp

#include "launcher.h"

#include <cstdio>
#include <cstring>

int
Launcher::Run()
{
    uint32_t version = ReadVersion();

    return 0;
}

uint32_t
Launcher::ReadVersion(const char* file_path)
{
    if(!file_path) file_path = ".ver";

    char version_str[64] = "";
    {
        FILE* file = fopen(file_path, "r");
        if(!file) return -1;

        fscanf(file, "%s", version_str);

        fclose(file);
    }

    if(!strcmp(version_str, "ver-00")) return 0;
    if(!strcmp(version_str, "ver-01")) return 1;
    if(!strcmp(version_str, "ver-02")) return 2;
    return -1;
}
