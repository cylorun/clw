cmake_minimum_required(VERSION 3.27)
project(clw C)

set(CMAKE_C_STANDARD 11)

add_library(cJSON STATIC lib/cJSON-1.7.18/cJSON.c)
add_executable(clw
        src/clw.c
        include/management/window_manager.h
        src/management/window_manager.c
        src/management/command_manager.c
        include/management/command_manager.h
        include/clw.h
        src/management/hotkey_manager.c
        include/management/hotkey_manager.h
        src/management/reset_manager.c
        include/management/reset_manager.h
        src/util.c
        include/util.h
        src/instance.c
        include/instance.h
        src/config.c
        include/config.h
)

target_link_libraries(clw gdi32 Msimg32 cJSON)