
project(lifegame)

# 添加源文件
aux_source_directory(./ SRC_LIST)
aux_source_directory(./imgui_windows SRC_LIST)

set(LIFEGAME_INC_PATHS
    ${CMAKE_CURRENT_LIST_DIR}./
    ${CMAKE_CURRENT_LIST_DIR}./imgui_windows
    ${SAKAENGINE_INC_PATHS}
)

message(STATUS "LIFEGAME_INC_PATHS: ${LIFEGAME_INC_PATHS}")

set(LIFEGAME_INC_PATHS ${LIFEGAME_INC_PATHS} PARENT_SCOPE)

include_directories(${LIFEGAME_INC_PATHS})
link_libraries(sakaengine)
add_library(${PROJECT_NAME} ${SRC_LIST})
