/*********************************************

		frameCounter
					FPS計算処理

**********************************************/
#include "system_timer.h"
#include "common.h"
#include "debug_font.h"

#define FPS_MEASUREMENT_TIME (1.0)	//この秒数毎に更新


static int g_FrameCount;		//フレームカウンター
static int g_FPSBaseFrameCount;	//FPS計測用フレームカウンター
static double g_FPSBaseTime;	//FPS計測用時間
static float g_FPS;			//FPS
static double g_StaticFrameTime;

void InitFrame()
{
	g_FrameCount = 0;
	g_FPSBaseFrameCount = 0;
	g_FPSBaseTime = 0.0;
	g_FPS = 0.0f;
	g_StaticFrameTime = 0.0f;
}

void UninitFrame()
{

}

void UpdateFrame()
{

	g_FrameCount++;
	double time = SystemTimer_GetTime();
	if (time - g_FPSBaseTime >= FPS_MEASUREMENT_TIME) {
		g_FPS = (float)((g_FrameCount - g_FPSBaseFrameCount) / (time - g_FPSBaseTime));
		g_FPSBaseTime = time;
		g_FPSBaseFrameCount = g_FrameCount;
	}

}
void DrawFrame()
{
	DebugFont_Draw((int)SCREEN_WIDTH - 100, 50, "%.2f", g_FPS);

}

double StaticFrameTime()
{
	return g_StaticFrameTime;
}

void StaticFrameTime(double _time)
{
	g_StaticFrameTime = _time;
}

int GetFrameCounter()
{
	return g_FrameCount;
}