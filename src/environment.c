#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "environment.h"

Texture2D worldFloor;
Texture2D worldFurnitures;

CollisionBox wall;

CollisionBox getWall() {
  return wall;
}

InteractionPoint interactions[10];
int interactionCount = 0;
InteractionPoint  officeComputer;


InteractionPoint createInteraction(float w, float h, Vector2 size, Task task) {
  if(interactionCount > 10) {
      fprintf(stderr, "It's time to write a pointer for interactions bro! \nExceeded expected count: %d\n", interactionCount);
    exit(-1);
  }

  InteractionPoint newInteraction = {
    (CollisionBox){w,h, size},
    SEND_EMAIL,
    true
  };

  interactions[interactionCount] = newInteraction;
  interactionCount++;
  return newInteraction;
}

void interact(Entity *entity) {
  if(!entity->actions.interact) return;
  for(int i = 0; i < interactionCount; i++) {
    bool isEnabled = interactions[i].enabled;
    bool isTouching = boxOverlap(&entity->colBox, &interactions[i].bounds);
    if(isEnabled && isTouching) {
      startTask(interactions[i].task);
      freeze(entity);
      interactions[i].enabled = false;
    }
  }
}

void initEnvironment() {
  worldFloor = LoadTexture("assets/tiles/test/png/Office__Floor.png");
  worldFurnitures = LoadTexture("assets/tiles/test/png/Office__Furnitures.png");
  wall = (CollisionBox){
    100, 10,
    {50, 150}
  };

  officeComputer = createInteraction(
    13,15,
    (Vector2){330,205},
    SEND_EMAIL);
}

void DrawCollisionBox(CollisionBox box, Color color) {
  DrawRectangleLines(
    (int)box.pos.x,
    (int)box.pos.y,
    (int)box.w,
    (int)box.h,
    color
  );
}

void drawEnvironment() {
  DrawTexture(worldFloor, 0, 0, WHITE);
  DrawTexture(worldFurnitures, 0,0, WHITE);
  DrawCollisionBox(officeComputer.bounds, GREEN);
  //DrawCollisionBox(wall, RED);
}

void cleanEnvironment() {
  UnloadTexture(worldFloor);
  UnloadTexture(worldFurnitures);

}

