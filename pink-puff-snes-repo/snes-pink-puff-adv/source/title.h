#pragma once
typedef enum { TITLE_MAIN=0, TITLE_GAME } TitleState;
void titleInit(void); void titleUpdate(void); void titleDraw(void); void titleSetState(TitleState s);
