#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include "entity.h"

#define TITLE "The Graveyard Shift"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 360

RenderTexture2D renderer;
Texture2D floorTest;
Entity player;
CollisionDiamond sampleDia;

void init() {
  renderer = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
  SetTextureFilter(renderer.texture, TEXTURE_FILTER_POINT);

  floorTest = LoadTexture("assets/backgrounds/cyan_floor.png");
  player = createEntity();

  sampleDia = (CollisionDiamond){ 20,20, (Vector2){200, 100}};
}

void update() {
  updateEntity(&player);
  receivePlayerInputs(&player);
  updateEntityCollisionState(&player, sampleDia);
  //debugPrintCollisionState(&player);
}

void draw() {
  DrawTexture(floorTest, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, WHITE);
  displayDiamond(sampleDia, GREEN);
  displayDiamond(player.colDiamond, GREEN);
  drawEntity(&player);
}

void cleanup() {
  UnloadTexture(floorTest);
}

void drawRenderer() {
  float scale = fmin(
      (float)GetScreenWidth() /SCREEN_WIDTH,
      (float)GetScreenHeight() /SCREEN_HEIGHT
  );

  int scaledWidth = (int)(SCREEN_WIDTH * scale);
  int scaledHeight = (int)(SCREEN_HEIGHT * scale);
  int offsetX = (GetScreenWidth() - scaledWidth) / 2;
  int offsetY = (GetScreenHeight() - scaledHeight) / 2;

  DrawTexturePro(
      renderer.texture,
      (Rectangle){ 0, 0,SCREEN_WIDTH, -SCREEN_HEIGHT }, // Flip vertically
      (Rectangle){ offsetX, offsetY, scaledWidth, scaledHeight },
      (Vector2){ 0, 0 },
      0.0f,
      WHITE
  );
}

int main(void) {
  InitWindow(1280, 720, TITLE);
  init();

  while(!WindowShouldClose()) {
    update();
    BeginTextureMode(renderer);
      ClearBackground(BLACK);
      draw();
    EndTextureMode();

    BeginDrawing();
    drawRenderer();
    EndDrawing();
  }

  cleanup();
  return 0;
}
