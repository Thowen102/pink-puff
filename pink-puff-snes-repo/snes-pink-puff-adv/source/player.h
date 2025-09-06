#pragma once
#include <snes.h>
#define FIX(x) ((x) << 8)
typedef struct {
    s16 x, y, vx, vy;
    u8 onGround, facing, floating, canDouble;
    u8 dashTimer, dashCD, lives, stars, invuln;
} Player;
void playerInit(Player* p, s16 x, s16 y);
void playerUpdate(Player* p);
void playerDraw(Player* p);
