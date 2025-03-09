
project(lifegame)

set(PATHS
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/map
    ${CMAKE_CURRENT_LIST_DIR}/imgui_windows
)

# 添加源文件
foreach(PATH ${PATHS})
    aux_source_directory(${PATH} SRC_LIST)
endforeach()

set(LIFEGAME_INC_PATHS
    ${PATHS}
    ${SAKAENGINE_INC_PATHS}
)

message(STATUS "LIFEGAME_INC_PATHS: ${LIFEGAME_INC_PATHS}")

set(LIFEGAME_INC_PATHS ${LIFEGAME_INC_PATHS} PARENT_SCOPE)

include_directories(${LIFEGAME_INC_PATHS})
link_libraries(sakaengine)
add_library(${PROJECT_NAME} ${SRC_LIST})
