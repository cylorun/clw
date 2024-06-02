#include "../include/window_manager.h"
#include "../include/command_manager.h"
#include "../include/hotkey_manager.h"
#include "../include/config.h"
#include "../include/util.h"
#include "../lib/cJSON-1.7.18/cJSON.h"
#include <stdio.h>
#include <stdlib.h>

#define CLW_VERSION "v0.0.0"

InstanceList instanceList = {0};
CommandList commandList = {0};
HotkeyList hotkeyList = {0};

int runCommand(const char *line) {
    char **args = split(line, " ");
    executeCommand(&commandList, (const char **) args);
}

InstanceList *getInstanceList() {
    return &instanceList;
}

int main(int argc, char **argv) {
    printf("Running Culti %s\n", CLW_VERSION);

    registerDefaultCommands(&commandList);
    registerDefaultHotkeys(&hotkeyList);
    initConfigManager();

    while (1) {
        char *buffer = read_line();
        runCommand(buffer);
        free(buffer);
    }

    return 0;
}



