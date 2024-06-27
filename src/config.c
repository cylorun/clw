#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/cJSON-1.7.18/cJSON.h"
#include "../include/instance.h"

#define CONFIG_PATH "../config.json"

typedef struct {
    cJSON *config;
} ConfigManager;

static ConfigManager manager;

cJSON *loadJSONFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = (char *) malloc(length + 1);
    if (data == NULL) {
        fclose(file);
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }

    fread(data, 1, length, file);
    data[length] = '\0';

    fclose(file);

    cJSON *json = cJSON_Parse(data);
    free(data);

    return json;
}

int saveJSONFile(const char *filename, cJSON *json) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing: %s\n", filename);
        return 0;
    }

    char *data = cJSON_Print(json);
    if (data == NULL) {
        fclose(file);
        fprintf(stderr, "Error converting JSON to string\n");
        return 0;
    }

    fputs(data, file);
    free(data);

    fclose(file);

    return 1;
}

void addInstanceList(InstanceList *list) {
    cJSON *instances = cJSON_GetObjectItem(manager.config, "instances");
    if (instances != NULL && cJSON_IsArray(instances)) {
        cJSON_Delete(instances);
    }

    instances = cJSON_AddArrayToObject(manager.config, "instances");
    for (int i = 0; i < list->count; ++i) {
        cJSON_AddItemToArray(instances, cJSON_CreateString(list->instances[i].path));
    }
    saveJSONFile(CONFIG_PATH, manager.config);
}

void setDefaultConfig() {
    cJSON *defaultConfig = cJSON_CreateObject();
    cJSON_AddStringToObject(defaultConfig, "mmc_path", "");
    cJSON_AddNumberToObject(defaultConfig, "rows", 2);
    cJSON_AddNumberToObject(defaultConfig, "cols", 2);
    saveJSONFile(CONFIG_PATH, defaultConfig);
    cJSON_Delete(defaultConfig);
}

void initConfigManager() {
    manager.config = loadJSONFile(CONFIG_PATH);
    if (!manager.config) {
        setDefaultConfig();
        manager.config = loadJSONFile(CONFIG_PATH);
    }
}

void cleanupConfigManager() {
    if (manager.config) {
        cJSON_Delete(manager.config);
        manager.config = NULL;
    }
}

cJSON *getConfig() {
    return manager.config;
}

const char* getConfigString(const char *key) {
    cJSON *item = cJSON_GetObjectItem(manager.config, key);
    return item ? cJSON_GetStringValue(item) : NULL;
}

int getConfigInt(const char *key) {
    cJSON *item = cJSON_GetObjectItem(manager.config, key);
    return item ? item->valueint : 0;
}

void setConfigString(const char *key, const char *value) {
    cJSON *item = cJSON_GetObjectItem(manager.config, key);
    if (item) {
        cJSON_SetValuestring(item, value);
    } else {
        cJSON_AddStringToObject(manager.config, key, value);
    }
    saveJSONFile(CONFIG_PATH, manager.config);
}

void setConfigInt(const char *key, int value) {
    cJSON *item = cJSON_GetObjectItem(manager.config, key);
    if (item) {
        cJSON_SetNumberValue(item, value);
    } else {
        cJSON_AddNumberToObject(manager.config, key, value);
    }
    saveJSONFile(CONFIG_PATH, manager.config);
}