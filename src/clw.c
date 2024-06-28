#include "../include/management/window_manager.h"
#include "../include/management/command_manager.h"
#include "../include/management/hotkey_manager.h"
#include "../include/config.h"
#include "../include/util.h"
#include "../include/logging.h"
#include <stdio.h>
#include <stdlib.h>

#define CLW_VERSION "v0.0.0-beta.1"

static InstanceList instanceList = {0};
static CommandList commandList = {0};
static HotkeyList hotkeyList = {0};

static void init() {
    initConfigManager();

    registerDefaultCommands(&commandList);
    registerDefaultHotkeys(&hotkeyList);
}

static int runCommand(const char *line) {
    char **args = split(line, " ");
    executeCommand(&commandList, (const char **) args);
}

InstanceList *getInstanceList() {
    return &instanceList;
}

int main(int argc, char **argv) {
    clwLog(LEVEL_INFO, "Running Culti %s\n", CLW_VERSION);
    init();

    while (1) {
        char *buffer = read_line();
        runCommand(buffer);
        free(buffer);
    }

    return 0;
}



