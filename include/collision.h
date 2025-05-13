#include <raylib.h>

typedef struct {
  float w;
  float h;
  Vector2 pos;
  bool visible;
} CollisionBox;


typedef struct {
  float w,h;
  Vector2 pos;
} CollisionDiamond;

typedef struct {
  bool top, bottom, left, right;
} CollisionState;


void displayColBox(CollisionBox *colBox);
void displayDiamond(CollisionDiamond diamond, Color color);

bool pointInDiamond(Vector2 p, CollisionDiamond d);
void getDiamondCorners(CollisionDiamond d, Vector2 out[4]);
