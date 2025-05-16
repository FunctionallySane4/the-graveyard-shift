#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include "collision.h"

// NEED A MAJOR OVERHAUL/REWRITE by using ldtk!

CollisionBox createCollisionBox(float w, float h) {
  return (CollisionBox) {w, h};
}

bool boxOverlap(CollisionBox *a, CollisionBox *b) {
  // Get the edges of box A
  float aLeft = a->pos.x;
  float aRight = aLeft + a->w;
  float aTop = a->pos.y;
  float aBottom = aTop + a->h;

  // Get the edges of box B
  float bLeft = b->pos.x;
  float bRight = bLeft + b->w;
  float bTop = b->pos.y;
  float bBottom = bTop + b->h;

  // Check for overlap using Axis-Aligned Bounding Box (AABB)
  return (aRight > bLeft &&
          aLeft < bRight &&
          aBottom > bTop &&
          aTop < bBottom);
}

bool isPointInBox(Vector2 point, CollisionBox box) {
    return (point.x >= box.pos.x && point.x <= (box.pos.x + box.w) &&
            point.y >= box.pos.y && point.y <= (box.pos.y + box.h));
}

