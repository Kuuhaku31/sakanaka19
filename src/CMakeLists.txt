
add_subdirectory(sakaengine)
add_subdirectory(sekibako)
add_subdirectory(lifegame)

# 添加源文件目录
aux_source_directory(./launcher DIR_SRC)
set(DIR_SRC ${DIR_SRC} ./main.cpp)

# 添加头文件目录
include_directories(
    ./launcher
    ${SEKIBAKO_INC_PATHS}
    ${LIFEGAME_INC_PATHS}
)

# 添加依赖
# 添加sekibako库
link_libraries(sekibako lifegame)

# 创建可执行文件
add_executable(sakanaka19 ${DIR_SRC})
