

#include "enemy.h"
#include "texture.h"
#include "common.h"
#include "sprite.h"
#include "input.h"

ENEMY g_enemy[ENEMY_MAX];

int g_enemyTexture;

void InitEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].isUse = false;
	}
	g_enemyTexture = TextureSetLoadFile("kuri.png", 128, 128);

}

void UninitEnemy()
{

}

void UpdateEnemy()
{
	if (Keyboard_IsTrigger(DIK_SPACE)) createEnemy(200, 200, 128);


	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].isUse) {

			g_enemy[i].position.move(2, 0);

			wrap(g_enemy[i].position.x, 0.0f, SCREEN_WIDTH);


			g_enemy[i].collision.Update(g_enemy[i].position);

		}
	}
}

void DrawEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].isUse) {
			spriteDraw(g_enemyTexture, { g_enemy[i].position.x,g_enemy[i].position.y },
				g_enemy[i].width,
				g_enemy[i].height
			);
		}
	}
}

void createEnemy(float x, float y, float size)
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (!g_enemy[i].isUse)
		{
			g_enemy[i].position = { x,y };
			g_enemy[i].isUse = true;
			g_enemy[i].collision.x = x;
			g_enemy[i].collision.y = y;
			g_enemy[i].width = size;
			g_enemy[i].height = size;
			g_enemy[i].collision.radius = size * 0.5f; //enemysize * 0.5f
			break;
		}
	}
}

void destroyEnemy(int _i)
{
	if (g_enemy[_i].isUse)
	{
		g_enemy[_i].position = { NULL,NULL };
		g_enemy[_i].isUse = false;
		g_enemy[_i].collision.x = NULL;
		g_enemy[_i].collision.y = NULL;
		g_enemy[_i].width = NULL;
		g_enemy[_i].height = NULL;
		g_enemy[_i].collision.radius = NULL;
	}
}


ENEMY *getEnemy()
{
	return g_enemy;
}
