#include "window_manager.h"
#include "command_manager.h"
#include "hotkey_manager.h"
#include <stdio.h>
#include <stdlib.h>

#define TOK_DELIMS " \t\r\n\a"
#define TOK_BUF 4
#define LINE_BUF 512

InstanceList instanceList = {0};
CommandList commandList = {0};
HotkeyList hotkeyList = {0};
char *read_line(void) {
    int buff_size = LINE_BUF;
    int pos = 0;
    char *buffer = malloc(sizeof(char) * buff_size);

    if (!buffer) {
        printf("allocation failure\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        char c = (char) getchar();
        if (c == EOF || c == '\n') {
            buffer[pos] = '\0';
            return buffer;
        }

        buffer[pos] = c;
        pos++;
        if (pos >= buff_size) {
            buff_size += 2;
            buffer = realloc(buffer, sizeof(char) * buff_size);
            if (!buffer) {
                printf("allocation failure\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **split_line(const char *line) {
    int buff_size = TOK_BUF;
    int pos = 0;
    char **tokens = malloc(sizeof(char *) * buff_size);
    char *token;

    if (!tokens) {
        printf("allocation failure\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIMS);
    while (token != NULL) {
        tokens[pos] = token;
        pos++;
        if (pos >= buff_size) {
            buff_size += buff_size;
            tokens = realloc(tokens, sizeof(char *) * buff_size);
            if (!tokens) {
                printf("allocation failure\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TOK_DELIMS);
    }

    tokens[pos] = NULL;
    return tokens;
}

int runCommand(const char* line) {
    char **args = split_line(line);
    executeCommand(&commandList, (const char **) args);
}

InstanceList *getInstanceList() {
    return &instanceList;
}

CommandList *getCommandList() {
    return &commandList;
}

int main(int argc, char **argv) {
    getAllOpenInstances(&instanceList);
    registerDefaultCommands(&commandList);
    registerDefaultHotkeys(&hotkeyList);
    printf("culti gaming\n");

    while (1) {
        char* buffer = read_line();
        runCommand(buffer);
        free(buffer);
    }

    return 0;
}



