#include "title.h"
#include "level.h"
#include <snes.h>
static TitleState st=TITLE_MAIN;
void titleSetState(TitleState s){st=s;}
void titleInit(void){ consoleInit(); consoleInitText(0, 15*2, &font); setScreenOn(); }
void center(u8 y,const char* m){ u8 x=(32-strlen(m))/2; consoleDrawText(x,y,m); }
void titleUpdate(void){ u16 k=padsCurrent(0); if(st==TITLE_MAIN){ if(k&KEY_START){ st=TITLE_GAME; levelLoad(0);} } else { levelUpdate(); } }
void titleDraw(void){ consoleClear(); if(st==TITLE_MAIN){ center(10,"PINK PUFF — SNES"); center(14,"Press START"); } else { levelDraw(); } }
