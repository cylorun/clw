#include "../../include/clw.h"
#include "../../include/command_manager.h"
#include "../../include/util.h"
#include "../../include/window_manager.h"
#include <stdio.h>

void registerCommand(CommandList *list, const char *name, CommandFunction function, int minArgs, int maxArgs) {
    if (list->count < MAX_COMMANDS) {
        Command *newCommand = &list->commands[list->count++];
        newCommand->name = name;
        newCommand->function = function;
        newCommand->minArgs = minArgs;
        newCommand->maxArgs = maxArgs;
    } else {
        perror("too many commands");
    }
}

void executeCommand(const CommandList *list, const char **args) {
    int argc = 0;
    while (args[argc] != NULL) {
        argc++;
    }

    if (argc == 0) {
        printf("No command given\n");
        return;
    }

    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->commands[i].name, args[0]) == 0) {
            if (argc - 1  < list->commands[i].minArgs || argc - 1 > list->commands[i].maxArgs) {
                printf("Incorrect argument count\n");
                return;
            }

            list->commands[i].function(args + 1);
            return;
        }
    }
    printf("%s is not a command\n", args[0]);
}

void registerDefaultCommands(CommandList *list) {
    registerCommand(list, "rd", &redetect, 0, 0);
    registerCommand(list, "help", &help, 0, 0);
    registerCommand(list, "titles", &titles, 0, 0);
    registerCommand(list, "config", &config, 0, 10);
    registerCommand(list, "close", &close, 1, MAX_INSTANCES);
    registerCommand(list, "launch", &launch, 1, MAX_INSTANCES);

}

void help(const char **args) {
    printf("<------->\n  help\n  rd\n  titles\n  config\n close\n launch\n");
}

void redetect(const char **args) {
    redetectInstances(getInstanceList());
}

void titles(const char **args) {
    InstanceList *list = getInstanceList();
    if (list->count < 1) {
        printf("No instances detected, will not set titles\n");
        return;
    }
    setAllTitles(list);
}

void config(const char **args) {

}

void close(const char **args) {
    InstanceList *list = getInstanceList();
    int num = atoi(args[1]);
    char *path = list->instances[num - 1].path;


}

void launch(const char **args) {
    InstanceList *list = getInstanceList();
    int num = atoi(args[1]);
    char *path = list->instances[num - 1].path;
    char *name = getInstanceName(path);
    launchInstance(name);
}
