
project(test00)
include_directories(./test00)
add_executable(${PROJECT_NAME}
    ./test00/main.cpp
    ./test00/testgame.cpp
)

project(test01)

include_directories(${SAKAENGINE_INC_PATHS})
link_libraries(sakaengine)
add_executable(${PROJECT_NAME}
    ./test01/main.cpp
)