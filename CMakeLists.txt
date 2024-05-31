cmake_minimum_required(VERSION 3.27)
project(culti C)

set(CMAKE_C_STANDARD 11)
include_directories(lib/cJSON-1.7.18)
include_directories(lib/Nuklear-4.12.0/include)


add_executable(culti culti.c
        window_manager.h
        window_manager.c
        command_manager.c
        command_manager.h
        culti.h
        hotkey_manager.c
        hotkey_manager.h
        reset_manager.c
        reset_manager.h
)

target_link_libraries(culti gdi32 Msimg32)
