/*********************************************

		frameCounter
					FPS�v�Z����

**********************************************/
#include "system_timer.h"
#include "common.h"
#include "debug_font.h"

#define FPS_MEASUREMENT_TIME (1.0)	//���̕b�����ɍX�V


static int g_FrameCount;		//�t���[���J�E���^�[
static int g_FPSBaseFrameCount;	//FPS�v���p�t���[���J�E���^�[
static double g_FPSBaseTime;	//FPS�v���p����
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