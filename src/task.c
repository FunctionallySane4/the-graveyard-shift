#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "task.h"
#include "entity.h"
#include "raylib.h"
#include "string.h"

Texture2D typingScreen;
Texture2D typingScreenFrenzy;
Task currentTask = NONE;

void finishTask() {
  currentTask = -1;
}

const char* emailToType = "Hi Featherly,\nHope you're doing well.\nand that migration season hasn't been too chaotic on your end.\n\nJust looping back around on the Q1 breadcrumb distribution report.\nEverything's looking good on our side, though we did have a minor hiccup\nwhen the intern accidentally fed an entire baguette to the test flock.\nNo long-term damage (except to the baguette),\nbut we might need to re-run the pecking efficiency metrics.\n\nWe're aiming to have the final numbers to you by Thursday,\nLet us know if you need any data visualizations,\nor if your team is still allergic to pie charts.\n\nThanks again for your patience,\nH.R. Ghoulman";
char currentEmail[MAX_INPUT_CHAR + 1];
int letterCount = 0;
int frenzyLetters = 0;
bool frenzyState = false;

char zombify(const char input) {
  if(letterCount < 1) return input;
  if(!frenzyState) return input;
  frenzyLetters++;
  switch(currentEmail[letterCount - 1]) {
    case 'b': return 'r';
    case 'r': return 'a';
    case 'a': return 'i';
    case 'i': return 'n';
    case 'n': return 's';
    default: return 'b';
}
}

bool canType;
float frenzyTimer;
float target = 0.0;
void randomFrenzy() {
  frenzyTimer += GetFrameTime();
  if(frenzyTimer > target && letterCount > 0) {
    frenzyState = true;
  }
}

void resetFrenzyTarget() {
  srand(time(NULL));
  frenzyTimer = 0.0;
  target = rand() % 10;
}

void decFrenzyLetter() {
  if(frenzyLetters > 0) {
    frenzyLetters--;
  } else {
    resetFrenzyTarget();
    frenzyState = false;
  }
}

float typeStart = 0;

void delayTypeStart() {
  if(!canType) typeStart += GetFrameTime();
  if(typeStart >= 0.1) {
    canType = true;
    typeStart = 0;
    resetFrenzyTarget();
  }
}

void typingTaskUpdate() {
  delayTypeStart();
  if(!canType) return;
  int key = GetCharPressed();
  if(!frenzyState) randomFrenzy();
  while (key > 0) {
    if (key >= 32 && key <= 126 && letterCount < MAX_INPUT_CHAR) {
      currentEmail[letterCount] = zombify((char)key);
      letterCount++;
      currentEmail[letterCount] = '\0';  // Null terminate
    }

    key = GetCharPressed();  // Get next char pressed (if any)
  }
  if (IsKeyPressed(KEY_ENTER) && letterCount < MAX_INPUT_CHAR) {
    currentEmail[letterCount] = '\n';
    letterCount++;
    currentEmail[letterCount] = '\0';
  }
  if (IsKeyPressed(KEY_BACKSPACE) && letterCount < MAX_INPUT_CHAR) {
    if(letterCount < 1) return;
    decFrenzyLetter();
    letterCount--;
    currentEmail[letterCount] = '\0';
  }

  if(letterCount >= strlen(emailToType)) finishTask();
}

void typingTaskDraw() {
  const int bodyX = 150;
  const int bodyY = 90;
  const float screenShakeX = rand() % 5;
  const float screenShakeY = rand() % 5;
  if(frenzyState ) {
    DrawTexture(typingScreenFrenzy, 0 + screenShakeX, 0 + screenShakeY, WHITE);
    DrawText(emailToType, bodyX + screenShakeX, bodyY + screenShakeY, 10, (Color){ 220, 220, 220, 255 });
    DrawText(currentEmail, bodyX + screenShakeX, bodyY + screenShakeY, 10, RED);
  } else {
    DrawTexture(typingScreen, 0,0, WHITE);
    DrawText(emailToType, bodyX, bodyY, 10, (Color){ 220, 220, 220, 255 });
    DrawText(currentEmail, bodyX, bodyY, 10, BLACK);
  }
}


void initTasks() {
  typingScreen = LoadTexture("assets/typing-screen.png");
  typingScreenFrenzy = LoadTexture("assets/typing-screen-frenzy.png");
}

void drawTasks() {
  switch(currentTask) {
    case SEND_EMAIL: typingTaskDraw();
    default: return;
  }
}

void updateTasks() {
  switch(currentTask) {
    case SEND_EMAIL: typingTaskUpdate();
    default: return;
  }
}

void cleanTasks() {
  UnloadTexture(typingScreen);
}

void setTask(Task taskToSet) {
  currentTask = taskToSet;
}

void startTask(const Task taskGiven) {
  if(taskGiven > DELIVER || taskGiven < NONE) {
    fprintf(stderr, "Task is invalid! Enum: %d\n", taskGiven);
    exit(-1);
  }
  setTask(taskGiven);
}
