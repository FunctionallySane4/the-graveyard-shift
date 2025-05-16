#include <raylib.h>
#include "collision.h"
#define ZOMBIE_SPR "assets/entities/zombie.png"
#define ENTITY_SPEED 30

typedef struct {
  bool moveLeft;
  bool moveRight;
  bool moveUp;
  bool moveDown;
  bool interact;
} ActionState;

typedef struct {
  Texture2D sprite;
  Vector2 pos;
  Vector2 vel;
  CollisionBox colBox;
  CollisionState colState;
  ActionState actions;
  bool canMove;
} Entity;


Entity createEntity();
void drawEntity(Entity *entity);
void updateEntity(Entity *entity);

void updateEntityCollisionState(Entity *entity, CollisionBox box);
void debugPrintCollisionState(Entity *entity);

void receivePlayerInputs(Entity *entity);

void freeze(Entity *entity);
void unfreeze(Entity *entity);
