#pragma once
#include <snes.h>
#define TILE_EMPTY 0
#define TILE_GROUND 1
#define TILE_CLOUD 2
#define TILE_GOAL 3
#define TILE_CHECK 4
#define TILE_SPIKE 5
typedef struct { const u16 *map; u16 w,h; const s16 *stars; u16 nStars; const s16 *walkers; u16 nWalkers; const s16 *floaters; u16 nFloaters; s16 spawnX,spawnY,goalX,goalY; } LevelDef;
extern u16 cameraX, cameraY;
void levelLoad(u8 idx); void levelRestart(void); void levelUpdate(void); void levelDraw(void);
u8 levelCollideSolid(s16 x,s16 y,s16 w,s16 h); u8 levelCollideCloud(s16 x,s16 y,s16 w,s16 h,u8 dropping);
void levelPlayerHurt(void); u8 levelAllStarsCollected(void); u8 getCurrentLevel(void);
