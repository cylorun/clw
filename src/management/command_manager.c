#include "../../include/clw.h"
#include "../../include/management/command_manager.h"
#include "../../include/util.h"
#include "../../include/management/window_manager.h"
#include "../../include/logging.h"
#include <stdio.h>


// commands
static void help(const char **args) {
    clwLog(LEVEL_INFO, "<------->\n  help\n  rd\n  titles\n  config\n close\n launch");
}

static void redetect(const char **args) {
    redetectInstances(getInstanceList());
}

static void titles(const char **args) {
    InstanceList *list = getInstanceList();
    if (list->count < 1) {
        clwLog(LEVEL_WARN, "No instances detected, will not set titles");
        return;
    }
    setAllTitles(list);
}

static void config(const char **args) {

}

static void close(const char **args) {
    InstanceList *list = getInstanceList();
    int num = getInstanceNumber(args[0]);

    char *path = list->instances[num - 1].path;
    char *name = getInstanceName(path);


}

static void launch(const char **args) {
    if (strcmp("all", args[0]) == 0) {
        launchAllInstances();
    } else {
        launchInstance(args[0]);
    }
}


void registerDefaultCommands(CommandList *list) {
    registerCommand(list, "rd", &redetect, 0, 0);
    registerCommand(list, "help", &help, 0, 0);
    registerCommand(list, "titles", &titles, 0, 0);
    registerCommand(list, "config", &config, 0, 10);
    registerCommand(list, "close", &close, 1, MAX_INSTANCES);
    registerCommand(list, "launch", &launch, 1, MAX_INSTANCES);

}

void registerCommand(CommandList *list, const char *name, CommandFunction function, int minArgs, int maxArgs) {
    if (list->count < MAX_COMMANDS) {
        Command *newCommand = &list->commands[list->count++];
        newCommand->name = name;
        newCommand->function = function;
        newCommand->minArgs = minArgs;
        newCommand->maxArgs = maxArgs;
    } else {
        clwLog(LEVEL_ERROR, "TOo many comands loaded");
        exit(EXIT_FAILURE);
    }
}

void executeCommand(const CommandList *list, const char **args) {
    int argc = 0;
    while (args[argc] != NULL) {
        argc++;
    }

    if (argc == 0) {
        clwLog(LEVEL_WARN, "No command given");
        return;
    }

    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->commands[i].name, args[0]) == 0) {
            if (argc - 1 < list->commands[i].minArgs || argc - 1 > list->commands[i].maxArgs) {
                clwLog(LEVEL_WARN, "Incorrect argument count");
                return;
            }

            list->commands[i].function(args + 1);
            return;
        }
    }
    clwLog(LEVEL_WARN, "%s is not a command\n", args[0]);
}
