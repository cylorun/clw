#include <stdio.h>
#include <ctype.h>
#include "../include/instance.h"
#include "../include/util.h"
#include "../include/window_manager.h"
#include "../include/config.h"

int getInstanceNumber(const char *name) {
    int i = 0;
    int count = 0;
    char c = name[i];
    char *nums = malloc(sizeof(char) * 10);
    if (nums == NULL) {
        perror("allocation failure\n");
        exit(EXIT_FAILURE);
    }

    while (c != '\0') {
        if (isdigit(c)) {
            nums[count++] = c;
        }
        c = name[++i];
    }
    nums[count] = '\0';

    int result = atoi(nums);
    free(nums);
    return result;
}

char *getInstanceName(char *path) {
    char **s = split(path, "/");
    int i = 0;
    while (s[i] != NULL) {
        i++;
    }

    return s[i - 2];
}

char *getInstancePath(MinecraftInstance *instance) {
    if (instance == NULL) {
        printf("Invalid instance\n");
        return NULL;
    }
    int pid = getPID(instance->hwnd);
    char command[128];
    snprintf(command, sizeof(command), "wmic process where processId=\"%d\" get CommandLine", pid);


    char *res = NULL;
    char *wmicout = run_cmd(command);


    char *s = replace(split(split(wmicout, ".path=")[1], " ")[0], "natives", ""); // top 10 most safe lines of code
    if (s) {
        res = s;
    }

    return res;
}

int launchMultiMC() {
    cJSON *config = getConfig();
    cJSON *mmc_path_item = cJSON_GetObjectItem(config, "mmc_path");
    char *mmc_path;

    if (mmc_path_item != NULL && cJSON_IsString(mmc_path_item)) {
        mmc_path = mmc_path_item->valuestring;
    } else {
        printf("Error: mmc_path is not a valid string or doesn't exist.\n");
        return 0;
    }
    system(mmc_path);
    return 0;
}


int launchInstance(const char *inst_name) {
    cJSON *config = getConfig();
    cJSON *mmc_path_item = cJSON_GetObjectItem(config, "mmc_path");
    char *mmc_path;

    if (mmc_path_item != NULL && cJSON_IsString(mmc_path_item)) {
        mmc_path = mmc_path_item->valuestring;
    } else {
        printf("Error: mmc_path is not a valid string or doesn't exist.\n");
        return 0;
    }

    char command[strlen(inst_name) + strlen(mmc_path) + 50];
    sprintf(command, "\"%s\" --launch %s", mmc_path, inst_name);
    printf("Running: %s\n", command);

    int result = system(command);
    if (result != 0) {
        printf("Error: MultiMC command failed with code %d\n", result);
        return 0;
    }

    return 1;
}

int launchAllInstances() {
    cJSON *config = getConfig();
    cJSON *instances = cJSON_GetObjectItem(config, "instances");

    if (instances == NULL || !cJSON_IsArray(instances)) {
        printf("Error: No saved instances detected.\n");
        cJSON_Delete(config);
        return 0;
    }

    int size = cJSON_GetArraySize(instances);
    for (int i = 0; i < size; ++i) {
        cJSON *curr = cJSON_GetArrayItem(instances, i);
        if (cJSON_IsString(curr)) {
            char* name = getInstanceName(curr->valuestring);
            launchInstance(name);
        }
    }

}
