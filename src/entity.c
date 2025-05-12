#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "entity.h"

Entity createEntity() {
  return (Entity){
    LoadTexture(ZOMBIE_SPR),
    (Vector2){250,120}
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

  if(entity->actions.moveLeft) entity->vel.x = -getStepValue(ENTITY_SPEED);
  if(entity->actions.moveRight) entity->vel.x = getStepValue(ENTITY_SPEED);
  if(entity->actions.moveUp) entity->vel.y = -getStepValue(ENTITY_SPEED);
  if(entity->actions.moveDown) entity->vel.y = getStepValue(ENTITY_SPEED);
}

void updateEntity(Entity *entity) {
  if(entity == NULL) {
    fprintf(stderr, "Entity Error: arg passed to updateEntity is invalid");
    return;
  }
  entity->pos.x += entity->vel.x;
  entity->pos.y += entity->vel.y;
  deltaAction(entity);

}


// PLAYER - might want to shove to another module
void receivePlayerInputs(Entity *entity) {
  entity->actions.moveLeft = IsKeyDown(KEY_LEFT);
  entity->actions.moveRight = IsKeyDown(KEY_RIGHT);
  entity->actions.moveUp = IsKeyDown(KEY_UP);
  entity->actions.moveDown = IsKeyDown(KEY_DOWN);
}
