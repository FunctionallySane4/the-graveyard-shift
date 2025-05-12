#include <raylib.h>
#define ZOMBIE_SPR "assets/entities/zombie.png"
#define ENTITY_SPEED 30

typedef struct {
  bool moveLeft;
  bool moveRight;
  bool moveUp;
  bool moveDown;
} ActionState;

typedef struct {
  Texture2D sprite;
  Vector2 pos;
  Vector2 vel;
  ActionState actions;
} Entity;


Entity createEntity();
void drawEntity(Entity *entity);
void updateEntity(Entity *entity);
void receivePlayerInputs(Entity *entity);
