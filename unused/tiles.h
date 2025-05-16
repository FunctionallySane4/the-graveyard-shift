#include "string.h"
#include "cJSON.h"
cJSON *loadLDTK(const char *filename);
cJSON* findLevelByName(cJSON *world, const char *levelName);
cJSON* findLayerByName(cJSON *level, const char *layerName);
