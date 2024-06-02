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


    char *s = replace(split(split(wmicout, ".path=")[1], " ")[0], "natives",
                      ".minecraft"); // top 10 most safe lines of code
    if (s) {
        res = s;
    }

    return res;
}

int launchInstance(const char *name) {
    cJSON *config = getConfig();
    char *mmc_path = (char *) cJSON_GetObjectItem(config, "mmc_path");
    if (mmc_path == NULL) {
        printf("No mmc_path defined");
        return 0;
    }

    char command[strlen(name) + strlen(mmc_path) + 20];
    sprintf(command, "%s --launch %s", mmc_path, name);
    system(command);

    return 1;
}
