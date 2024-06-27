#include "../../include/management/window_manager.h"
#include "../../include/util.h"
#include "../../include/instance.h"
#include "../../include/config.h"
#include <stdio.h>
#include <tchar.h>

static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char buffer[MAX_WIN_NAME_LEN];
    InstanceList *instanceList = (InstanceList *) lParam;

    if (IsWindowVisible(hwnd) && GetWindowTextA(hwnd, buffer, sizeof(buffer)) > 0 &&
        strstr(buffer, MC_PATTERN) != NULL) {
        if (instanceList->count < MAX_INSTANCES) {
            instanceList->instances[instanceList->count].hwnd = hwnd;

            char *path = getInstancePath(&instanceList->instances[instanceList->count]);
            int instNum = getInstanceNumber(getInstanceName(path));

            instanceList->instances[instanceList->count].num = instNum;
            instanceList->instances[instanceList->count].path = path;
            instanceList->count++;

        } else {
            perror("too many instances");
        }
    }
    return TRUE;
}

DWORD getPID(HWND hwnd) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    return pid;
}

void getAllOpenInstances(InstanceList *instanceList) {
    memset(instanceList, 0, sizeof(InstanceList));
    EnumWindows(EnumWindowsProc, (LPARAM) instanceList);
}

void setWindowText(HWND hwnd, char *text) {
    SetWindowTextA(hwnd, text);
}

void setWindowPosAndSize(HWND hwnd, int x, int y, int w, int h) {
    SetWindowPos(hwnd, NULL, x, y, w, h, 0);
}

void setWindowPos(HWND hwnd, int x, int y) {
    SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void setWindowSize(HWND hwnd, int w, int h) {
    SetWindowPos(hwnd, NULL, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
}


void setAllTitles(const InstanceList *instanceList) {
    for (int i = 0; i < instanceList->count; ++i) {
        char num[3];
        itoa(instanceList->instances[i].num, num, 10);

        char newTitle[MAX_WIN_NAME_LEN];
        snprintf(newTitle, sizeof(newTitle), "Minecraft* - Instance %s", num);

        setWindowText(instanceList->instances[i].hwnd, newTitle);
    }
}

void redetectInstances(const InstanceList *list) {
    getAllOpenInstances(list);
    setAllTitles(list);
    resizeAll(list);
    sortInstances(list);
    addInstanceList(list);
}

void resizeAll(const InstanceList *instanceList) {
    int w = 1920, h = 400;
    for (int i = 0; i < instanceList->count; ++i) {
        MinecraftInstance inst = instanceList->instances[i];
        setWindowPosAndSize(inst.hwnd, 0, 0, w, h);
    }
}

char *getForegroundText() {
    HWND hwnd = GetForegroundWindow();
    char *buffer = malloc(MAX_WIN_NAME_LEN);
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    GetWindowText(hwnd, buffer, MAX_WIN_NAME_LEN);
    buffer[MAX_WIN_NAME_LEN - 1] = '\0';
    return buffer;
}

char *getActiveText() {
    HWND hwnd = GetActiveWindow();
    char *buffer = malloc(MAX_WIN_NAME_LEN);
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    GetWindowText(hwnd, buffer, MAX_WIN_NAME_LEN);
    buffer[MAX_WIN_NAME_LEN - 1] = '\0';
    return buffer;
}

HWND getWindowByName(char *name) {
    return FindWindow(_T(name), NULL); //DOES NOT WORK!!
}

void sendKeyStroke(HWND hwnd, WPARAM key) {
    if (hwnd == NULL) {
        printf("Invalid window handle.\n");
        return;
    }

    SetActiveWindow(hwnd);

    LPARAM lParam = (MapVirtualKey(key, MAPVK_VK_TO_VSC) << 16) | 1;

    if (!PostMessageA(hwnd, WM_KEYDOWN, key, lParam)) {
        printf("Failed to send WM_KEYDOWN message.\n");
    }

    lParam = (MapVirtualKey(key, MAPVK_VK_TO_VSC) << 16) | (1 << 30) | (1 << 31);
    if (!PostMessageA(hwnd, WM_KEYUP, key, lParam)) {
        printf("Failed to send WM_KEYUP message.\n");
    }
}

int isOnProjector() {
    return strstr(getForegroundText(), "Projector (Scene)") != NULL ? 1 : 0;
}
