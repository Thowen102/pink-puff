#include "level.h"
#include "player.h"
#include <snes.h>
static Player gPlayer; u8 curLevel=0; u16 cameraX=0,cameraY=0;
#define MAP_W 64
#define MAP_H 32
static u16 MAP[MAP_W*MAP_H];
static inline u16 mapAt(s16 tx,s16 ty){ if(tx<0||ty<0||tx>=MAP_W||ty>=MAP_H) return TILE_GROUND; return MAP[ty*MAP_W+tx]; }
u8 levelCollideSolid(s16 x,s16 y,s16 w,s16 h){ s16 x0=(x>>8)>>3,y0=(y>>8)>>3,x1=((x+w)>>8)>>3,y1=((y+h)>>8)>>3; for(s16 ty=y0;ty<=y1;ty++) for(s16 tx=x0;tx<=x1;tx++){u16 t=mapAt(tx,ty); if(t==TILE_GROUND||t==TILE_SPIKE) return 1;} return 0; }
u8 levelCollideCloud(s16 x,s16 y,s16 w,s16 h,u8 dropping){ if(dropping) return 0; s16 feet=((y+h)>>8)>>3; s16 x0=(x>>8)>>3, x1=((x+w)>>8)>>3; for(s16 tx=x0;tx<=x1;tx++){ if(mapAt(tx,feet)==TILE_CLOUD) return 1;} return 0; }
void levelPlayerHurt(void){ if(gPlayer.invuln) return; if(gPlayer.lives) gPlayer.lives--; gPlayer.invuln=120; gPlayer.x=FIX(32); gPlayer.y=FIX(120); gPlayer.vx=gPlayer.vy=0; gPlayer.floating=0; gPlayer.canDouble=1; gPlayer.onGround=0; }
u8 levelAllStarsCollected(void){ return 1; }
void levelLoad(u8 idx){ (void)idx; // simple single map
  // clear
  for(int i=0;i<MAP_W*MAP_H;i++) MAP[i]=0;
  // ground
  for(int y=MAP_H-3;y<MAP_H;y++) for(int x=0;x<MAP_W;x++) MAP[y*MAP_W+x]=TILE_GROUND;
  // clouds
  for(int x=6;x<12;x++) MAP[(MAP_H-6)*MAP_W+x]=TILE_CLOUD;
  for(int x=14;x<18;x++) MAP[(MAP_H-8)*MAP_W+x]=TILE_CLOUD;
  for(int x=22;x<26;x++) MAP[(MAP_H-10)*MAP_W+x]=TILE_CLOUD;
  // goal
  MAP[(MAP_H-4)*MAP_W + (MAP_W-6)] = TILE_GOAL;
  playerInit(&gPlayer, FIX(32), FIX(120)); cameraX=0; cameraY=0;
}
void levelRestart(void){ levelLoad(curLevel); }
void levelUpdate(void){
  playerUpdate(&gPlayer);
  u16 px=gPlayer.x>>8; if(px>120 && px<(MAP_W*8-120)) cameraX=px-120;
}
void levelDraw(void){
  bgSetScroll(0,cameraX,0); bgSetScroll(1,cameraX/2,-8);
  playerDraw(&gPlayer);
}
u8 getCurrentLevel(void){ return curLevel; }
