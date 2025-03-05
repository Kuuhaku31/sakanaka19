
project(sekibako)

set(PATHS
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/game
    ${CMAKE_CURRENT_LIST_DIR}/game/collision_manager
    ${CMAKE_CURRENT_LIST_DIR}/game/effect_master
    ${CMAKE_CURRENT_LIST_DIR}/debug
    ${CMAKE_CURRENT_LIST_DIR}/imgui_windows
    ${CMAKE_CURRENT_LIST_DIR}/player
    ${CMAKE_CURRENT_LIST_DIR}/player/player_states
    ${CMAKE_CURRENT_LIST_DIR}/player/player_effects
)

set(SRC_PATH
    ${PATHS}
)

set(SEKIBAKO_INC_PATHS
    ${SAKAENGINE_INC_PATHS}
    ${PATHS}
)

set(SEKIBAKO_INC_PATHS
    ${SEKIBAKO_INC_PATHS}
    PARENT_SCOPE
)

foreach(p ${SRC_PATH})
    aux_source_directory(${p} SRC)
endforeach()

message(STATUS "Main Project SRC: ${SRC}")
message(STATUS "Main Project SEKIBAKO_INC_PATHS: ${SEKIBAKO_INC_PATHS}")

include_directories(${SEKIBAKO_INC_PATHS})
link_libraries(sakaengine)
add_library(${PROJECT_NAME} ${SRC})
