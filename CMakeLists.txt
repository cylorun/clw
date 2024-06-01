cmake_minimum_required(VERSION 3.27)
project(culti C)

set(CMAKE_C_STANDARD 11)
include_directories(lib/cJSON-1.7.18)
include_directories(lib/Nuklear-4.12.0/include)


add_executable(culti src/culti.c
        src/management/window_manager.h
        src/management/window_manager.c
        src/management/command_manager.c
        src/management/command_manager.h
        src/culti.h
        src/management/hotkey_manager.c
        src/management/hotkey_manager.h
        src/management/reset_manager.c
        src/management/reset_manager.h
        src/util.c
        src/util.h
        src/instance.c
        src/instance.h
)

target_link_libraries(culti gdi32 Msimg32)
