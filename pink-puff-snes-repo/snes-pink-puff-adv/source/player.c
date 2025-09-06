#include "player.h"
#include "level.h"
#include <snes.h>
static const s16 GRAVITY=230, FLOAT_G=64, MOVE_ACC=90, MAX_X=1280, JUMP_PWR=-3584, DASH_SPD=3072, AIR_DRAG=235, FRIC=205;
static inline s16 clamp(s16 v,s16 lo,s16 hi){return v<lo?lo:(v>hi?hi:v);}
void playerInit(Player* p, s16 x, s16 y){p->x=x;p->y=y;p->vx=p->vy=0;p->onGround=0;p->facing=1;p->floating=0;p->canDouble=1;p->dashTimer=0;p->dashCD=0;p->lives=3;p->stars=0;p->invuln=0;}
void playerUpdate(Player* p){
    u16 k=padsCurrent(0); s16 ax=0; if(k&KEY_LEFT){ax-=MOVE_ACC;p->facing=0;} if(k&KEY_RIGHT){ax+=MOVE_ACC;p->facing=1;} p->vx+=ax;
    static u8 jh=0; u8 up=(k&(KEY_B|KEY_A))!=0; if(up&&!jh){ if(p->onGround){p->vy=JUMP_PWR;p->onGround=0;p->canDouble=1;p->floating=0;} else if(p->canDouble){p->vy=(JUMP_PWR*9)/10;p->canDouble=0;p->floating=1;} } jh=up;
    p->floating=(!p->onGround&&up)?1:0;
    if((k&(KEY_X|KEY_Y))&&!p->dashTimer&&!p->dashCD){p->dashTimer=8;p->vy=(p->vy*50)/100;p->vx=p->facing?DASH_SPD:-DASH_SPD;p->dashCD=40;}
    if(p->dashCD) p->dashCD--;
    p->vy += p->dashTimer?0:(p->floating?FLOAT_G:GRAVITY);
    p->vx=clamp(p->vx,-MAX_X,MAX_X); p->vy=clamp(p->vy,-5120,5120);
    s16 ox=p->x, oy=p->y; p->x+=p->vx; p->y+=p->vy;
    extern u8 levelCollideSolid(s16,s16,s16,s16); extern u8 levelCollideCloud(s16,s16,s16,s16,u8);
    u8 drop=(k&KEY_DOWN)!=0;
    if(p->vy>=0 && levelCollideCloud(p->x,p->y,FIX(16),FIX(30),drop)){ p->y=(p->y&0xFF00); p->vy=0;p->onGround=1;p->floating=0;p->canDouble=1;}
    else if(levelCollideSolid(p->x,p->y,FIX(16),FIX(30))){ p->y=oy; p->x=ox+p->vx; if(levelCollideSolid(p->x,p->y,FIX(16),FIX(30))){p->x=ox;p->vx=0;} if(p->vy>0){p->onGround=1;p->vy=0;p->floating=0;p->canDouble=1;} }
    else p->onGround=0;
    p->vx = (p->onGround?FRIC:AIR_DRAG)*p->vx>>8;
    if(p->invuln) p->invuln--; if((p->y>>8)>240) levelPlayerHurt();
}
void playerDraw(Player* p){
    extern u16 PLAYER_TILE; u16 px=p->x>>8, py=p->y>>8, tid=PLAYER_TILE; if(p->floating&&!p->onGround) tid+=8; else if(p->onGround&&(p->vx>>8)) tid+=4;
    u8 hf=p->facing?0:OBJ_HFLIP; for(u8 i=0;i<4;i++){u16 dx=(i&1)?8:0, dy=(i&2)?8:0; oamSet(i,px+dx,py+dy,2,0,0,tid+i,0); oamSetEx(i,OBJ_SMALL,OBJ_SHOW); oamSetAttr(i,hf,0,0);}
}
