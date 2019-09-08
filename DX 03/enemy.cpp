

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
		g_enemy[i].move = { 1.0f,0.0f };
	}
	g_enemyTexture = TextureSetLoadFile("kuri.png", 128, 128);

}

void UninitEnemy()
{

}

void UpdateEnemy()
{
	if(Keyboard_IsTrigger(DIK_SPACE)) createEnemy(200, 200, 32);


	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].isUse) {

			g_enemy[i].position.x += 2;

			wrap(g_enemy[i].position.x, 0.0f, SCREEN_WIDTH);

			g_enemy[i].collision.x = g_enemy[i].position.x;
			g_enemy[i].collision.y = g_enemy[i].position.y;
		}
	}
}

void DrawEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].isUse) {
			spriteDraw(g_enemyTexture, g_enemy[i].position);
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
			g_enemy[i].collision.radius = size * 0.5; //enemysize * 0.5f
			break;
		}
	}
}

ENEMY *getEnemy()
{
	return g_enemy;
}
