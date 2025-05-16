#include "entity.h"
#include "task.h"

typedef struct {
  CollisionBox bounds;
  Task task;
  bool enabled;
} InteractionPoint;

void initEnvironment();
void wallCollisions(Entity *entity);
void cleanEnvironment();
void drawEnvironment();
void interact(Entity *entity);
