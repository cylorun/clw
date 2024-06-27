#ifndef CONFIG_H
#define CONFIG_H

#include "lib/cJSON-1.7.18/cJSON.h"
#include "include/instance.h"

#define CONFIG_PATH "../config.json"

typedef struct {
    cJSON *config;
} ConfigManager;


cJSON *loadJSONFile(const char *filename);

int saveJSONFile(const char *filename, cJSON *json);

void addInstanceList(InstanceList *list);

void setDefaultConfig();

void initConfigManager();

void cleanupConfigManager();

cJSON *getConfig();

const char *getConfigString(const char *key);

int getConfigInt(const char *key);

void setConfigString(const char *key, const char *value);

void setConfigInt(const char *key, int value);

#endif