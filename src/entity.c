#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include "entity.h"

Entity createEntity() {
  return (Entity){
    LoadTexture(ZOMBIE_SPR),
    (Vector2){250,120},
    (Vector2){0,0},
    (CollisionDiamond){5, 3}
  };
}
void drawEntity(Entity *entity) {
  //animate(entity);
  DrawTexture(entity->sprite, entity->pos.x, entity->pos.y, WHITE);
}

float getStepValue(float mult) {
  return GetFrameTime() * mult;
}

void deltaAction(Entity *entity) {
  entity->vel.x = 0;
  entity->vel.y = 0;

  bool canMoveUp = !entity->colState.top;
  bool canMoveDown = !entity->colState.bottom;
  bool canMoveLeft = !entity->colState.left;
  bool canMoveRight = !entity->colState.right;

  if(entity->actions.moveLeft & canMoveLeft) entity->vel.x = -getStepValue(ENTITY_SPEED);
  if(entity->actions.moveRight & canMoveRight) entity->vel.x = getStepValue(ENTITY_SPEED);
  if(entity->actions.moveUp & canMoveUp) entity->vel.y = -getStepValue(ENTITY_SPEED);
  if(entity->actions.moveDown & canMoveDown) entity->vel.y = getStepValue(ENTITY_SPEED);
}

void updateEntityCollision(Entity *entity) {
  const int offsetY = 64 / 2 + (64 / 4);
  const int offsetX = 64 / 2;
  entity->colDiamond = (CollisionDiamond){
    entity->colDiamond.w,
    entity->colDiamond.h,
    (Vector2){entity->pos.x + offsetX, entity->pos.y + offsetY},
  };
}

void updateEntity(Entity *entity) {
  if(entity == NULL) {
    fprintf(stderr, "Entity Error: arg passed to updateEntity is invalid");
    return;
  }
  entity->pos.x += entity->vel.x;
  entity->pos.y += entity->vel.y;
  deltaAction(entity);
  updateEntityCollision(entity);
}


void updateEntityCollisionState(Entity *entity, CollisionDiamond d) {
  CollisionState state = { 0 };  // Reset collision state

  Vector2 corners[4];
  getDiamondCorners(entity->colDiamond, corners);

  if (pointInDiamond(corners[0], d)) state.top = true;
  if (pointInDiamond(corners[1], d)) state.right = true;
  if (pointInDiamond(corners[2], d)) state.bottom = true;
  if (pointInDiamond(corners[3], d)) state.left = true;

  entity->colState = state;  // Always overwrite with updated state
}

void debugPrintCollisionState(Entity *entity) {
    printf("Collision State:\n");

    if (entity->colState.top)    printf("  - Collision on TOP\n");
    if (entity->colState.bottom) printf("  - Collision on BOTTOM\n");
    if (entity->colState.left)   printf("  - Collision on LEFT\n");
    if (entity->colState.right)  printf("  - Collision on RIGHT\n");

    if (!entity->colState.top && !entity->colState.bottom &&
        !entity->colState.left && !entity->colState.right)
    {
        printf("  - No collision detected\n");
    }
}


// PLAYER - might want to shove to another module
void receivePlayerInputs(Entity *entity) {
  entity->actions.moveLeft = IsKeyDown(KEY_LEFT);
  entity->actions.moveRight = IsKeyDown(KEY_RIGHT);
  entity->actions.moveUp = IsKeyDown(KEY_UP);
  entity->actions.moveDown = IsKeyDown(KEY_DOWN);
}
