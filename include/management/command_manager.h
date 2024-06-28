#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include <string.h>
#include <stdio.h>

#define MAX_COMMANDS 100

typedef void (*CommandFunction)(const char **args);

typedef struct {
    char *name;
    int minArgs;
    int maxArgs;
    CommandFunction function;
} Command;

typedef struct {
    Command commands[MAX_COMMANDS];
    int count;
} CommandList;


void registerCommand(CommandList *list, const char *name, CommandFunction function, int minArgs, int maxArgs);

void executeCommand(const CommandList *list, const char **args);

void registerDefaultCommands(CommandList *list);

#endif
