#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <windows.h>

#define MC_PATTERN "Minecraft*"
#define MAX_INSTANCES 100
#define MAX_WIN_NAME_LEN 256


typedef struct {
    HWND hwnd;
    int num;
} MinecraftInstance;

typedef struct {
    MinecraftInstance instances[MAX_INSTANCES];
    int count;
} InstanceList;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

DWORD getPID(HWND hwnd);

void getAllOpenInstances(InstanceList *instanceList);

void setWindowText(HWND hwnd, char *text);

void setWindowPosAndSize(HWND hwnd, int x, int y, int w, int h);

void setWindowSize(HWND hwnd, int w, int h);

void setWindowPos(HWND hwnd, int x, int y);

void setAllTitles(const InstanceList *instanceList);

void resizeAll(const InstanceList *instanceList);

char *getForegroundText();

char *getActiveText();

void sendKeyStroke(HWND hwnd, WPARAM key);

void sendCharKey(HWND hwnd, char c);

HWND getWindowByName(char *name);

#endif