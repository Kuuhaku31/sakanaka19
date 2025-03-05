
// launcher.cpp

#include "launcher.h"

#include "versions.h"

#include <cJSON.h>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include <string>


struct InitInfo
{
    int32_t     version = -1;
    std::string resources;
};

InitInfo
ReadInfo(std::string file_path = "")
{
    InitInfo info;

    if(file_path.empty()) file_path = "ver.json";

    cJSON* root = nullptr;

    { // 读取 JSON 文件内容
        std::ifstream file(file_path);
        if(!file.is_open())
        {
            printf("Error: Cannot open file %s\n", file_path.c_str());
            return info;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string json_content = buffer.str();
        file.close();

        root = cJSON_Parse(json_content.c_str());
        if(root == nullptr)
        {
            printf("Error: Cannot parse JSON content\n");
            return info;
        }
    }


    { // 解析 JSON 文件内容
        cJSON* version_item = cJSON_GetObjectItem(root, "version");
        if(!version_item)
        {
            cJSON_Delete(root);
            return info;
        }

        cJSON* resources_item = cJSON_GetObjectItem(root, "resources_path");
        if(!resources_item)
        {
            cJSON_Delete(root);
            return info;
        }

        std::string version_str = cJSON_GetStringValue(version_item);
        if(version_str.empty())
        {
            cJSON_Delete(root);
            return info;
        }

        if(version_str == "ver-00") info.version = 0;
        if(version_str == "ver-01") info.version = 1;
        if(version_str == "ver-02") info.version = 2;
        if(version_str == "ver-03") info.version = 3;

        info.resources = cJSON_GetStringValue(resources_item);
    }

    cJSON_Delete(root);
    return info;
}


int
Run()
{
    InitInfo info = ReadInfo();
    if(info.version < 0)
    {
        printf("Error: ReadInfo()\n");
        return -1;
    }

    switch(info.version)
    {
    case 0:
        printf("Version 0\n");
        RunSEKIBAKO(info.resources.c_str());
        break;

    case 1:
        printf("Version 1\n");
        RunLifeGame();
        break;

    default:
        printf("Unknown version\n");
        break;
    }

    return 0;
}
