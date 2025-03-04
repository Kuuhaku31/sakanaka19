
// launcher.cpp

#include "launcher.h"

#include "versions.h"

#include <cstdint>
#include <cstdio>
#include <cstring>

uint32_t
ReadVersion(const char* file_path = nullptr)
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

int
Run()
{
    uint32_t version = ReadVersion();

    switch(version)
    {
    case 0:
        printf("Version 0\n");
        RunTest();
        break;

    default:
        printf("Unknown version\n");
        break;
    }

    return 0;
}
