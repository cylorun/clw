#ifndef CULTI_UTIL_H
#define CULTI_UTIL_H

#include "management/window_manager.h"

char **split(const char *line, const char *delim);

char *replace(const char *str, const char *old, const char *new);

char *read_line(void);

int contains(char** list, char* sub);

char *run_cmd(const char* command);

int compareNum(const void *a, const void *b);

void sortInstances(InstanceList *list);

int mousePosToIdx();

void handleAllocationFailure();


#endif
