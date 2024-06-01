#include "../../include/reset_manager.h"
#include "../../include/window_manager.h"


void resetAllInstances(InstanceList *list) {
    for (int i = 0; i < list->count; i++) {
        MinecraftInstance instance = list->instances[i];
        singleReset(instance);
    }
}

void singleReset(MinecraftInstance instance) {
    sendKeyStroke(instance.hwnd, VK_F6);
}

void focusReset(InstanceList *list) {

}
