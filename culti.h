#ifndef CULTI_CULTI_H
#define CULTI_CULTI_H

#include "window_manager.h"
#include "command_manager.h"

int runCommand(const char *line);

char *read_line(void);

char **split_line(const char *line);

InstanceList *getInstanceList();

CommandList *getCommandList();

int main();

#endif
