/*******************************************************

		bg.cpp
	
					バックグラウンド処理

********************************************************/
#include "bg.h"
#include "texture.h"
#include "sprite.h"
#include "common.h"
#include "scene.h"

#define BG_NUM 4

typedef struct
{
	float x;
	float y;
}BG;


BG g_bg[BG_NUM];

static int BGTexture = 0;

void InitBG()
{
	for (int i = 0; i < BG_NUM; i++)
	{
		g_bg[i].x = SCREEN_WIDTH * 0.5 + SCREEN_WIDTH * (i % 2);
		g_bg[i].y = SCREEN_HEIGHT * 0.5f + SCREEN_HEIGHT * (i / 2);
	}
	if (GetScene() == SCENE_RESULT)
		BGTexture = TextureSetLoadFile("rom/texture/bg_sunset.png");
	else
		BGTexture = TextureSetLoadFile("rom/texture/bg_sky.png");
	//BGTexture = TextureSetLoadFile("rom/texture/bg_night.png");
}

void UninitBG()
{

}

void UpdateBG()
{
	for (int i = 0; i < BG_NUM; i++)
	{
		g_bg[i].x--;
		if (g_bg[i].x + SCREEN_WIDTH * 0.5f < 0)
			g_bg[i].x = SCREEN_WIDTH * 0.5f + SCREEN_WIDTH - 1;
		g_bg[i].y--;
		if (g_bg[i].y + SCREEN_HEIGHT * 0.5f < 0)
			g_bg[i].y = SCREEN_HEIGHT * 0.5f + SCREEN_HEIGHT - 1;
	}
}

void DrawBG()
{
	for (int i = 0; i < BG_NUM; i++)
	{
		spriteDraw(
			BGTexture,
			{ g_bg[i].x,g_bg[i].y },
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			D3DCOLOR_RGBA(255, 255, 255, 255)
		);
	}
}