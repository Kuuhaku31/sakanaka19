
// config.cpp

#include "lifegame.h"
#include "lifegame_map.h"


inline void
load_size(cJSON* root_item, const char* label, Size& size)
{
    static cJSON* target_item = nullptr;
    static cJSON* value_item  = nullptr;

    target_item = cJSON_GetObjectItem(root_item, label);
    if(!target_item || !cJSON_IsObject(target_item)) return;

    value_item = cJSON_GetObjectItem(target_item, "w");
    if(value_item && cJSON_IsNumber(value_item)) size.w = value_item->valueint;
    value_item = cJSON_GetObjectItem(target_item, "h");
    if(value_item && cJSON_IsNumber(value_item)) size.h = value_item->valueint;
}

inline void
load_offset(cJSON* root_item, const char* label, Offset& offset)
{
    static cJSON* target_item = nullptr;
    static cJSON* value_item  = nullptr;

    target_item = cJSON_GetObjectItem(root_item, label);
    if(!target_item || !cJSON_IsObject(target_item)) return;

    value_item = cJSON_GetObjectItem(target_item, "dx");
    if(value_item && cJSON_IsNumber(value_item)) offset.dx = value_item->valueint;
    value_item = cJSON_GetObjectItem(target_item, "dy");
    if(value_item && cJSON_IsNumber(value_item)) offset.dy = value_item->valueint;
}

inline void
load_view(cJSON* root_item, const char* label, View& view)
{
    static cJSON* target_item = nullptr;
    static cJSON* value_item  = nullptr;

    target_item = cJSON_GetObjectItem(root_item, label);
    if(!target_item || !cJSON_IsObject(target_item)) return;

    value_item = cJSON_GetObjectItem(target_item, "center_x");
    if(value_item && cJSON_IsNumber(value_item)) view.MoveCenterTo(value_item->valuedouble, view.viewCenterY());
    value_item = cJSON_GetObjectItem(target_item, "center_y");
    if(value_item && cJSON_IsNumber(value_item)) view.MoveCenterTo(view.viewCenterX(), value_item->valuedouble);
    value_item = cJSON_GetObjectItem(target_item, "unit_size");
    if(value_item && cJSON_IsNumber(value_item)) view.SetUnitSize(value_item->valuedouble);
}


inline void
save_size(cJSON* root_item, const char* label, const Size& size)
{
    static cJSON* node = nullptr;

    node = cJSON_CreateObject();
    cJSON_AddItemToObject(node, "w", cJSON_CreateNumber(size.w));
    cJSON_AddItemToObject(node, "h", cJSON_CreateNumber(size.h));

    cJSON_AddItemToObject(root_item, label, node);
}

inline void
save_offset(cJSON* item, const char* label, const Offset& offset)
{
    static cJSON* node = nullptr;

    node = cJSON_CreateObject();
    cJSON_AddItemToObject(node, "dx", cJSON_CreateNumber(offset.dx));
    cJSON_AddItemToObject(node, "dy", cJSON_CreateNumber(offset.dy));

    cJSON_AddItemToObject(item, label, node);
}

inline void
save_view(cJSON* root_item, const char* label, const View& view)
{
    static cJSON* node = nullptr;

    node = cJSON_CreateObject();
    cJSON_AddItemToObject(node, "center_x", cJSON_CreateNumber(view.viewCenterX()));
    cJSON_AddItemToObject(node, "center_y", cJSON_CreateNumber(view.viewCenterY()));
    cJSON_AddItemToObject(node, "unit_size", cJSON_CreateNumber(view.unitSize()));

    cJSON_AddItemToObject(root_item, label, node);
}


void
LifeGame::ProcessInitConfig(cJSON* root)
{
    load_size(root, "display_size", LifeGameMap::display_size);
    load_size(root, "view_display_size", LifeGameMap::view_display_size);
    load_offset(root, "view_offset", LifeGameMap::view_offset);
    load_view(root, "map_view", LifeGameMap::map_view);
}

void
LifeGame::ProcessSaveConfig(cJSON* root)
{
    save_size(root, "display_size", LifeGameMap::display_size);
    save_size(root, "view_display_size", LifeGameMap::view_display_size);
    save_offset(root, "view_offset", LifeGameMap::view_offset);
    save_view(root, "map_view", LifeGameMap::map_view);
}
