
#include <math.h>
#include "star.h"
#include "texture.h"
#include "sprite.h"
#include "frameCounter.h"
#include "common.h"

#define STARSPEED 4
#define STARLIFE 40


STAR g_star[STAR_MAX];
unsigned int g_StarTexture;

void InitStar()
{
	g_StarTexture = TextureSetLoadFile("rom/texture/exp.png");
	for (int i = 0; i < STAR_MAX; i++)
	{
		g_star[i].pos.x = 0;
		g_star[i].pos.y = 0;
		g_star[i].width = 32.0f;
		g_star[i].height = 32.0f;
		g_star[i].col.radius = g_star[i].width*0.5f;
		g_star[i].addScore = 0;
		g_star[i].dir = 0;
		g_star[i].isUse = false;
	}
}

void UpdateStar()
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (UsedStar(i))
		{
			g_star[i].frame++;
			g_star[i].pos.move((float)cos(g_star[i].dir) * STARSPEED, (float)sin(g_star[i].dir) * STARSPEED);
			g_star[i].col.Update(g_star[i].pos);

			//if (!isInside(g_star[i].pos.x, 0.0f, SCREEN_WIDTH))
			//	DeleteStar(i);

			//if (!isInside(g_star[i].pos.y, 0.0f, SCREEN_HEIGHT))
			//	DeleteStar(i);


			if (g_star[i].frame > STARLIFE)
				DeleteStar(i);
		}
	}
}

void DrawStar()
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (UsedStar(i))
			spriteDrawDivAnim(
				g_StarTexture,
				{ g_star[i].pos.x,g_star[i].pos.y },
				g_star[i].width * 3,
				g_star[i].height * 3,
				8, 8, 8 * 8,
				1,
				0, 63,
				D3DCOLOR_RGBA(255, 255, 255, 255)
			);
		//spriteDraw(
		//	g_StarTexture,
		//	{ g_star[i].pos.x,g_star[i].pos.y },
		//	g_star[i].width,
		//	g_star[i].height,
		//	D3DCOLOR_RGBA(255, 255, 255, 255)
		//);
	}
}

void CreateStar(float x, float y, float dir, int count)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (UsedStar(i))
			continue;

		g_star[i].pos.x = x;
		g_star[i].pos.y = y;
		g_star[i].dir = dir;
		g_star[i].frame = 0;
		g_star[i].isUse = true;
		g_star[i].HitCount = count + 1;
		g_star[i].addScore = pow(2, count);
		break;
	}
}

void DeleteStar(int id)
{
	if (UsedStar(id))
	{
		g_star[id].isUse = false;
		g_star[id].addScore = 0;
	}
}


bool UsedStar(int id)
{
	return g_star[id].isUse;
}

STAR *GetStar()
{
	return g_star;
}

int GetAddScoreStar(int id)
{
	return g_star[id].addScore;
}