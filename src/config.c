#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/cJSON-1.7.18/cJSON.h"

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

void setDefaultConfig() {
    cJSON *nj = cJSON_CreateObject();
    cJSON_AddStringToObject(nj, "mmc_path", "");
    cJSON_AddNumberToObject(nj, "rows", 2);
    cJSON_AddNumberToObject(nj, "cols", 2);
    saveJSONFile(CONFIG_PATH, nj);
}

void initConfigManager() {
    FILE *file = fopen(CONFIG_PATH, "r");
    if (!file) {
        setDefaultConfig();
    }
    fclose(file);
    manager.config = loadJSONFile(CONFIG_PATH);
}

cJSON *getConfig() {
    return manager.config;
}





