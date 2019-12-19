/****************************************

		enemy
					oŒ»‚·‚é“G‚Ìˆ—

******************************************/

#include "enemy.h"
#include "texture.h"
#include "common.h"
#include "sprite.h"
#include "input.h"
#include "star.h"
#include "frameCounter.h"
#include "score.h"
#include "sound.h"

ENEMY g_enemy[ENEMY_MAX];

int g_enemyTexture;

void InitEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].isUse = false;
		g_enemy[i].width = 40.0f;
		g_enemy[i].height = 40.0f;
		g_enemy[i].vel.x = 3.0f;
		g_enemy[i].vel.y = 0.25f;
		g_enemy[i].collision.radius = g_enemy[i].width * 0.5f; //enemysize * 0.5f
	}
	g_enemyTexture = TextureSetLoadFile("rom/texture/bird.png");

}

void UninitEnemy()
{

}

void UpdateEnemy()
{
	if (GetFrameCounter() % (int)((rand() % (int)SecondsToFrame(0.4)) + SecondsToFrame(0.2)) == 0)
		createEnemy(rand() % (int)(SCREEN_WIDTH - g_enemy->width * 2) + g_enemy->width, g_enemy->height);


	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].isUse) {
			g_enemy[i].position.move(g_enemy[i].vel.x, g_enemy[i].vel.y);

			rebound(g_enemy[i].position.x, g_enemy[i].width*0.5f, g_enemy[i].vel.x, 1.0f, 0.0f, SCREEN_WIDTH, false);
			rebound(g_enemy[i].position.y, g_enemy[i].height*0.5f, g_enemy[i].vel.y, 0.93f, 0.0f, SCREEN_HEIGHT, false);
			clamp(g_enemy[i].position.y, 0.0f, SCREEN_HEIGHT - g_enemy[i].height*0.5f);

			g_enemy[i].vel.y += 0.125f;
			g_enemy[i].collision.Update(g_enemy[i].position);

		}
	}
}

void DrawEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].isUse) {
			spriteDraw(g_enemyTexture,
				{ g_enemy[i].position.x,g_enemy[i].position.y },
				g_enemy[i].width,
				g_enemy[i].height,
				D3DCOLOR_RGBA(255, 255, 255, 255)
			);
		}
	}
}

void createEnemy(float x, float y)
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (!g_enemy[i].isUse)
		{
			g_enemy[i].position = { x,y };
			g_enemy[i].isUse = true;
			g_enemy[i].vel.x = 3.0f;
			g_enemy[i].vel.y = 0.25f;
			break;
		}
	}
}

void destroyEnemy(int _i)
{
	if (g_enemy[_i].isUse)
	{
		g_enemy[_i].isUse = false;
	}
}


ENEMY *getEnemy()
{
	return g_enemy;
}
