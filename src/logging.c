#include "../include/logging.h"
#include <time.h>
#include <stdio.h>

static char *getLevelName(enum LogLevel level) {
    switch (level) {
        case LEVEL_INFO:
            return "INFO";
        case LEVEL_WARN:
            return "WARN";
        case LEVEL_ERROR:
            return "ERROR";
        case LEVEL_DEBUG:
            return "DEBUG";
        default:
            return "UNKNOWN";
    }
}

static void getCurrentTime(char *buffer, size_t size) {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, size, "%H:%M:%S", timeinfo);
}

void clwLog(enum LogLevel logLevel, char *msg) {
    char *level = getLevelName(logLevel);
    char currTime[9];
    getCurrentTime(currTime, sizeof currTime);
    printf("[%s/%s] %s", currTime, level, msg);
}
