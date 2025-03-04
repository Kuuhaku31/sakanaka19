
add_subdirectory(sakaengine)

# 添加源文件目录
aux_source_directory(./launcher DIR_SRC)
set(DIR_SRC ${DIR_SRC} ./main.cpp)

# 添加头文件目录
include_directories(./launcher)

# 创建可执行文件
add_executable(sakanaka19 ${DIR_SRC})
