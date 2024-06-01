#ifndef CULTI_CULTI_H
#define CULTI_CULTI_H

#include "management/window_manager.h"
#include "management/command_manager.h"

int runCommand(const char *line);

char *read_line(void);

InstanceList *getInstanceList();

int main(int argc, char **argv);

#endif
