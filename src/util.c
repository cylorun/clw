#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/util.h"
#include "../include/management/window_manager.h"
#include "../include/logging.h"

#define TOK_BUF 512
#define LINE_BUF 512


char *read_line(void) {
    int buff_size = LINE_BUF;
    int pos = 0;
    char *buffer = malloc(sizeof(char) * buff_size);

    if (!buffer) {
       handleAllocationFailure();
       return NULL;
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
            buff_size += buff_size;
            buffer = realloc(buffer, sizeof(char) * buff_size);
            if (!buffer) {
                handleAllocationFailure();
                return NULL;
            }
        }
    }
}

char **split(const char *line, const char* delim) {
    int buff_size = TOK_BUF;
    int pos = 0;
    char **tokens = malloc(sizeof(char *) * buff_size);
    char *token;

    if (!tokens) {
        handleAllocationFailure();
        return NULL;
    }

    token = strstr(line, delim);
    while (token != NULL) {
        tokens[pos] = malloc(token - line + 1);
        if (!tokens[pos]) {
            handleAllocationFailure();
            return NULL;
        }

        strncpy(tokens[pos], line, token - line);
        tokens[pos][token - line] = '\0';
        pos++;
        if (pos >= buff_size) {
            buff_size += buff_size;
            tokens = realloc(tokens, sizeof(char *) * buff_size);
            if (!tokens) {
                handleAllocationFailure();
                return NULL;
            }
        }
        line = token + strlen(delim);
        token = strstr(line, delim);
    }

    tokens[pos] = malloc(strlen(line) + 1);
    if (!tokens[pos]) {
        handleAllocationFailure();
        return NULL;
    }
    strcpy(tokens[pos], line);
    pos++;

    tokens[pos] = NULL;
    return tokens;
}

char *replace(const char *str, const char *old, const char *new) {
    int old_len = strlen(old);
    int new_len = strlen(new);
    int count = 0;
    const char *p = str;
    while ((p = strstr(p, old)) != NULL) {
        count++;
        p += old_len;
    }

    int final_len = strlen(str) + count * (new_len - old_len) + 1;
    char *result = (char *)malloc(final_len * sizeof(char));
    if (result == NULL) {
        handleAllocationFailure();
        return NULL;
    }

    const char *start = str;
    char *write_pos = result;
    while (1) {
        const char *p = strstr(start, old);
        if (p == NULL) {
            strcpy(write_pos, start);
            break;
        }

        int len = p - start;
        strncpy(write_pos, start, len);
        write_pos += len;
        strcpy(write_pos, new);
        write_pos += new_len;
        start = p + old_len;
    }

    return result;
}

char *run_cmd(const char* command) {
    FILE *fp = _popen(command, "r");
    if (fp == NULL) {
        clwLog(LEVEL_ERROR, "Failed to run command: %s", command);
        return NULL;
    }

    char buffer[2048];
    char *result = NULL;
    int size = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        int len = strlen(buffer);
        result = realloc(result, size + len + 1);
        memcpy(result + size, buffer, len);
        size += len;
        result[size] = '\0';
    }
    return result;
}

int contains(char** list, char* sub) {
    int i = 0;
    char* curr = list[i];
    while (curr != NULL) {
        if (strcmp(curr, sub) == 0) {
            return 1;
        }
        curr = list[i++];
    }

    return 0;
}

int compareNum(const void *a, const void *b) {
    const MinecraftInstance *instA = (const MinecraftInstance *) a;
    const MinecraftInstance *instB = (const MinecraftInstance *) b;
    return instA->num - instB->num;
}

void sortInstances(InstanceList *list) {
    qsort(list->instances, list->count, sizeof(MinecraftInstance), compareNum);
}

int mousePosToIdx() {
    POINT p;
    GetCursorPos(&p);

    int h = 1080;
    int w = 1920;
    int rows = 2;
    int cols = 2;

    int cell_width = w / cols;
    int cell_height = h / rows;

    int ci = p.x / cell_width;
    int ri = p.y / cell_height;

    return ri * cols + ci;
}

void handleAllocationFailure() {
    clwLog(LEVEL_ERROR, "Memory allocation failure");
    exit(EXIT_FAILURE);
}
