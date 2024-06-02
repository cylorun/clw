#ifndef CULTI_INSTANCE_H
#define CULTI_INSTANCE_H

#include <windows.h>

#define MAX_INSTANCES 100

typedef struct {
    HWND hwnd;
    int num;
    char* path;
} MinecraftInstance;

typedef struct {
    MinecraftInstance instances[MAX_INSTANCES];
    int count;
} InstanceList;

int getInstanceNumber(const char* name);

int launchInstance(const char* name);

int launchAllInstances();

int closeInstance(const char* name);


char *getInstanceName(char* path);

char* getInstancePath(MinecraftInstance *instance);

#endif
