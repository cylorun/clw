#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <windows.h>
#include "../instance.h"

#define MC_PATTERN "Minecraft*"
#define MAX_WIN_NAME_LEN 256


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

DWORD getPID(HWND hwnd);

void getAllOpenInstances(InstanceList *instanceList);

void setWindowText(HWND hwnd, char *text);

void setWindowPosAndSize(HWND hwnd, int x, int y, int w, int h);

void setWindowSize(HWND hwnd, int w, int h);

void setWindowPos(HWND hwnd, int x, int y);

void setAllTitles(const InstanceList *instanceList);

void resizeAll(const InstanceList *instanceList);

void redetectInstances(const InstanceList *list);

char *getForegroundText();

char *getActiveText();

void sendKeyStroke(HWND hwnd, WPARAM key);

HWND getWindowByName(char *name);

int isOnProjector();

#endif