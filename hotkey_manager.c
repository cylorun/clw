#include <stdio.h>
#include <pthread.h>
#include "hotkey_manager.h"
#include "window_manager.h"
#include "reset_manager.h"
#include "culti.h"

void addHotkey(HotkeyList *list, const char *name, int vKey, HotkeyFunction function) {
    if (list->count < MAX_HOTKEYS) {
        Hotkey *newKey = &list->hotkeys[list->count++];
        newKey->function = function;
        newKey->name = name;
        newKey->vKey = vKey;
    }
}

void processHotkeys(HotkeyList *list) {
    while (1) {
        for (int i = 0; i < list->count; ++i) {
            Hotkey key = list->hotkeys[i];
            if (GetAsyncKeyState(key.vKey) & 0x8000) {
                key.function();
            }
        }

        Sleep(100);
    }
}

void *hotkeyThread(void *arg) {
    HotkeyList *list = arg;
    processHotkeys(list);
}

void run(HotkeyList *list) {
    pthread_t id;
    pthread_create(&id, NULL, hotkeyThread, list);
}

void registerDefaultHotkeys(HotkeyList *list) {
    addHotkey(list, "reset-all", 0x54, &resetAll);
    run(list);
}

void resetAll() {
    if (strstr(getForegroundText(), "Projector (Scene)") != NULL) {
        resetAllInstances(getInstanceList());
        printf("reset all \n");
    }
}

