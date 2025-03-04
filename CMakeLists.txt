
cmake_minimum_required(VERSION 3.10)

# set the project name
project(sakanaka19)

# 设置所有生成的库和可执行文件的输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(src)
