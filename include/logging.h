#ifndef CLW_LOGGING_H
#define CLW_LOGGING_H

enum LogLevel {
    LEVEL_INFO,
    LEVEL_WARN,
    LEVEL_ERROR,
    LEVEL_DEBUG
};

void clwLog(enum LogLevel logLevel, char* format, ...);

#endif
