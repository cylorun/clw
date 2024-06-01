#include "../culti.h"
#include "command_manager.h"
#include "../util.h"
#include "window_manager.h"
#include <stdio.h>

void addCommand(CommandList *list, const char *name, CommandFunction function) {
    if (list->count < MAX_COMMANDS) {
        Command *newCommand = &list->commands[list->count++];
        newCommand->name = name;
        newCommand->function = function;
    } else {
        perror("too many commands");
    }
}

void executeCommand(const CommandList *list, const char **args) {
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->commands[i].name, args[0]) == 0) {
            list->commands[i].function(args + 1);
            return;
        }
    }
    printf("%s is not a command\n", args[0]);
}

void registerDefaultCommands(CommandList *list) {
    addCommand(list, "rd", &redetect);
    addCommand(list, "help", &help);
    addCommand(list, "titles", &titles);
}

void help(const char **args) {
    printf("<------->\n help\n redetect\n titles\n");
}

void redetect(const char **args) {
    redetectInstances(getInstanceList());
}

void titles(const char **args) {
    InstanceList *list = getInstanceList();
    setAllTitles(list);
}

