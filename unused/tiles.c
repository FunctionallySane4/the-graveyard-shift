#include <stdio.h>
#include <stdlib.h>
#include "tiles.h"

char *loadFile(const char *filename) {
    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *data = malloc(length + 1);
    fread(data, 1, length, f);
    data[length] = '\0';
    fclose(f);
    return data;
}

cJSON *loadLDTK(const char *filename) {
    char *text = loadFile(filename);
    cJSON *json = cJSON_Parse(text);
    free(text);
    return json;
}

cJSON* findLevelByName(cJSON *world, const char *levelName) {
    cJSON *levels = cJSON_GetObjectItem(world, "levels");
    if (!levels) return NULL;

    cJSON *level;
    cJSON_ArrayForEach(level, levels) {
        const char *name = cJSON_GetObjectItem(level, "identifier")->valuestring;
        if (strcmp(name, levelName) == 0) {
            return level;
        }
    }

    return NULL; // Not found
}

cJSON* findLayerByName(cJSON *level, const char *layerName) {
    cJSON *layers = cJSON_GetObjectItem(level, "layerInstances");
    if (!layers) return NULL;

    cJSON *layer;
    cJSON_ArrayForEach(layer, layers) {
        const char *name = cJSON_GetObjectItem(layer, "__identifier")->valuestring;
        if (strcmp(name, layerName) == 0) {
            return layer;
        }
    }

    return NULL; // Not found
}
