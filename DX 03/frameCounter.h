#ifndef _FRAMECOUNTER_H_
#define _FRAMECOUNTER_H_



void InitFrame();
void UninitFrame();
void UpdateFrame();
void DrawFrame();

double StaticFrameTime();
void StaticFrameTime(double _time);

int GetFlameCounter();

#endif // !_FRAMECOUNTER_H_
