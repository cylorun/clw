cmake_minimum_required(VERSION 3.27)
project(clw C)

set(CMAKE_C_STANDARD 11)

add_library(cJSON STATIC lib/cJSON-1.7.18/cJSON.c)
add_executable(clw
        clw.c
        include/management/window_manager.h
        management/window_manager.c
        management/command_manager.c
        include/management/command_manager.h
        include/clw.h
        management/hotkey_manager.c
        include/management/hotkey_manager.h
        management/reset_manager.c
        include/management/reset_manager.h
        util.c
        include/util.h
        instance.c
        include/instance.h
        config.c
        include/config.h
)

target_link_libraries(clw gdi32 Msimg32 cJSON)