#include <raylib.h>

typedef struct {
  float w;
  float h;
  Vector2 pos;
} CollisionBox;


typedef struct {
  bool top, bottom, left, right;
} CollisionState;


void displayColBox(CollisionBox *colBox);
bool boxOverlap(CollisionBox *a, CollisionBox *b);

bool isPointInBox(Vector2 point, CollisionBox box);

void DrawCollisionBox(CollisionBox box, Color color);

