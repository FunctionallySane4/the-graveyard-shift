#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include "environment.h"

#define TITLE "The Graveyard Shift"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 360

RenderTexture2D renderer;
Entity player;
Texture2D sampleTexture;

void init() {
  renderer = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
  SetTextureFilter(renderer.texture, TEXTURE_FILTER_POINT);

  player = createEntity();
  receivePlayerInputs(&player);
  unfreeze(&player);
  initEnvironment();
  initTasks();
}



void update() {
  updateEntity(&player);
  receivePlayerInputs(&player);
  interact(&player);
  updateTasks();
}

void draw() {
  drawEnvironment();
  drawEntity(&player);
  drawTasks();

//debug
  Vector2 mouse = GetMousePosition();

  char buffer[32];
  snprintf(buffer, sizeof(buffer), "(%.0f, %.0f)", mouse.x, mouse.y);

  // Draw at top-left corner of screen
  DrawText(buffer, 10, 10, 20, RAYWHITE);
}

void cleanup() {
  UnloadTexture(sampleTexture);
  cleanEnvironment();
  cleanTasks();
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
