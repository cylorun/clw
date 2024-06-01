#include "management/window_manager.h"
#include "management/command_manager.h"
#include "management/hotkey_manager.h"
#include "config.h"
#include "util.h"
#include "../lib/cJSON-1.7.18/cJSON.h"
#include <stdio.h>
#include <stdlib.h>

#define TOK_DELIMS " \t\r\n\a"
#define CULTI_VERSION "v0.0.0"


InstanceList instanceList = {0};
CommandList commandList = {0};
HotkeyList hotkeyList = {0};

int runCommand(const char *line) {
    char **args = split(line, TOK_DELIMS);
    executeCommand(&commandList, (const char **) args);
}

InstanceList *getInstanceList() {
    return &instanceList;
}

int main(int argc, char **argv) {
    printf("Running Culti %s\n", CULTI_VERSION);

    getAllOpenInstances(&instanceList);
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



