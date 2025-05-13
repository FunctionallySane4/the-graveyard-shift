#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include "collision.h"

CollisionBox createCollisionBox(float w, float h) {
  // TODO: OPTIMIZE TODAY!
  return (CollisionBox) {w, h};
}

void displayColBox(CollisionBox *colBox) {
  if(colBox->visible) {
    DrawRectangle(colBox->pos.x, colBox->pos.y, colBox->w, colBox->h, GREEN);
  }
}

bool pointInDiamond(Vector2 p, CollisionDiamond d) {
    float dx = fabsf(p.x - d.pos.x);  // Horizontal distance from the center
    float dy = fabsf(p.y - d.pos.y);  // Vertical distance from the center
    return (dx / d.w + dy / d.h) <= 1.0f;
}

bool diamondOverlap(CollisionDiamond a, CollisionDiamond b) {
    float dx = fabsf(a.pos.x - b.pos.x);
    float dy = fabsf(a.pos.y - b.pos.y);
    return (dx / ((a.w + b.w)/2) + dy / ((a.h + b.h)/2)) <= 1.0f;
}

void displayDiamond(CollisionDiamond d, Color color) { Vector2 top    = { d.pos.x, d.pos.y - d.h };
    Vector2 right  = { d.pos.x + d.w, d.pos.y };
    Vector2 bottom = { d.pos.x, d.pos.y + d.h };
    Vector2 left   = { d.pos.x - d.w, d.pos.y };

    Vector2 points[4] = { top, right, bottom, left };
    DrawLineV(points[0], points[1], color);
    DrawLineV(points[1], points[2], color);
    DrawLineV(points[2], points[3], color);
    DrawLineV(points[3], points[0], color);
}

void getDiamondCorners(CollisionDiamond d, Vector2 out[4]) {
    out[0] = (Vector2){ d.pos.x, d.pos.y - d.h / 2.0f }; // Top
    out[1] = (Vector2){ d.pos.x + d.w / 2.0f, d.pos.y }; // Right
    out[2] = (Vector2){ d.pos.x, d.pos.y + d.h / 2.0f }; // Bottom
    out[3] = (Vector2){ d.pos.x - d.w / 2.0f, d.pos.y }; // Left
}
