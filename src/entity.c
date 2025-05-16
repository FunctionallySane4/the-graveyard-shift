#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include "entity.h"

// TODO: switch to square to square collision instead

Entity createEntity() {
  return (Entity){
    LoadTexture(ZOMBIE_SPR),
    (Vector2){230,220},
    (Vector2){0,0},
    (CollisionBox){5, 3}
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

    float step = getStepValue(ENTITY_SPEED);

    // Horizontal movement
    if (entity->actions.moveLeft && !entity->colState.left) {
        entity->vel.x = -step;
    } else if (entity->actions.moveRight && !entity->colState.right) {
        entity->vel.x = step;
    }

    // Vertical movement
    if (entity->actions.moveUp && !entity->colState.top) {
        entity->vel.y = -step;
    } else if (entity->actions.moveDown && !entity->colState.bottom) {
        entity->vel.y = step;
    }
}

// Main collision state update function
void updateEntityCollisionState(Entity *entity, CollisionBox box) {
  CollisionState state = { 0 };  // Reset
  float aLeft = entity->colBox.pos.x;
  float aRight = aLeft + entity->colBox.w;
  float aTop = entity->colBox.pos.y;
  float aBottom = aTop + entity->colBox.h;

  float bLeft = box.pos.x;
  float bRight = bLeft + box.w;
  float bTop = box.pos.y;
  float bBottom = bTop + box.h;

  bool overlapX = aRight > bLeft && aLeft < bRight;
  bool overlapY = aBottom > bTop && aTop < bBottom;

  if (overlapX && overlapY) {
      float fromTop = aBottom - bTop;
      float fromBottom = bBottom - aTop;
      float fromLeft = aRight - bLeft;
      float fromRight = bRight - aLeft;

      float minOverlap = fminf(fminf(fromTop, fromBottom), fminf(fromLeft, fromRight));

      if (minOverlap == fromTop)    state.bottom = true;
      if (minOverlap == fromBottom) state.top = true;
      if (minOverlap == fromLeft)   state.right = true;
      if (minOverlap == fromRight)  state.left = true;
  }

  entity->colState = state;
}


void updateEntityCollision(Entity *entity) {
  const int offsetY = 64 / 2 + (64 / 4);
  const int offsetX = 64 / 2;
  entity->colBox = (CollisionBox){
    entity->colBox.w,
    entity->colBox.h,
    (Vector2){entity->pos.x + offsetX, entity->pos.y + offsetY},
  };
}

void updateEntity(Entity *entity) {
  if(entity == NULL) {
    fprintf(stderr, "Entity Error: arg passed to updateEntity is invalid");
    return;
  }

  if(entity->canMove) {
    entity->pos.x += entity->vel.x;
    entity->pos.y += entity->vel.y;
  }
  deltaAction(entity);
  updateEntityCollision(entity);
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
  entity->actions.interact = IsKeyDown(KEY_E);
  entity->actions.moveLeft = IsKeyDown(KEY_LEFT);
  entity->actions.moveRight = IsKeyDown(KEY_RIGHT);
  entity->actions.moveUp = IsKeyDown(KEY_UP);
  entity->actions.moveDown = IsKeyDown(KEY_DOWN);
}

void freeze(Entity *entity) {
  entity->canMove = false;
}

void unfreeze(Entity *entity) {
  entity->canMove = true;
}
