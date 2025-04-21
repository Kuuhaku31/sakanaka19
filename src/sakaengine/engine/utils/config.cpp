
// config.cpp

#include "sakaengine.h"

#include <fstream>
#include <sstream>


void
sakaengine::LoadConfig(const std::string& path, std::function<void(cJSON*)> process)
{
    if(path.empty() || !process) return;

    // 读取 JSON 文件内容
    // 如果文件不存在，则创建一个空文件
    std::ifstream file(path);
    if(!file.is_open())
    {
        printf("File %s does not exist, creating a new file...\n", path.c_str());
        std::ofstream new_file(path);
        if(new_file.is_open())
        {
            new_file.close();
            printf("File %s created successfully.\n", path.c_str());
        }
        else
        {
            printf("Error: Cannot create file %s\n", path.c_str());
            return;
        }
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string json_content = buffer.str();
    file.close();

    // 解析 JSON 文件内容
    cJSON* root = cJSON_Parse(json_content.c_str());
    if(!root) root = cJSON_CreateObject();

    process(root);

    cJSON_Delete(root);
}

void
sakaengine::SaveConfig(const std::string& path, std::function<void(cJSON*)> process)
{
    if(path.empty() || !process) return;

    cJSON* root = cJSON_CreateObject();

    process(root);

    // 写入 JSON 文件
    // 如果文件不存在，则创建一个空文件
    std::ofstream file(path);
    if(!file.is_open())
    {
        printf("File %s does not exist, creating a new file...\n", path.c_str());
        std::ofstream new_file(path);
        if(new_file.is_open())
        {
            new_file.close();
            printf("File %s created successfully.\n", path.c_str());
        }
        else
        {
            printf("Error: Cannot create file %s\n", path.c_str());
            return;
        }
    }

    std::string json_content = cJSON_Print(root);
    file << json_content;
    file.close();

    cJSON_Delete(root);
}
