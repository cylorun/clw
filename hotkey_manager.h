#ifndef CULTI_HOTKEY_MANAGER_H
#define CULTI_HOTKEY_MANAGER_H

#include <windows.h>

#define MAX_HOTKEYS 100

typedef void (*HotkeyFunction)(void);

typedef struct {
    char *name;
    int vKey;
    HotkeyFunction function;
} Hotkey;

typedef struct {
    Hotkey hotkeys[MAX_HOTKEYS];
    int count;
} HotkeyList;

void addHotkey(HotkeyList *list, const char *name, int vKey, HotkeyFunction function);

void processHotkeys(HotkeyList *list);

void *hotkeyThread(void *arg);

void run(HotkeyList *list);


void registerDefaultHotkeys(HotkeyList *list);

// commands

void resetAll();

#endif
