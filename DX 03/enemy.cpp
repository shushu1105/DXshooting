

#include "enemy.h"
#include "texture.h"
#include "common.h"
#include "sprite.h"

ENEMY g_enemy[ENEMY_MAX];
CIRCLE g_collisionEnemy;

int g_enemyTexture;
int g_flameCount;

void InitEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].isUse = false;
		g_enemy[i].move = { 1.0f,0.0f,0.0f,0.0f };
	}
	g_enemyTexture = TextureSetLoadFile("kuri.png", 128, 128);


	createEnemy(700.0f,300.0f);

}
void UninitEnemy()
{

}
void UpdateEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].isUse) {
			g_collisionEnemy.position.x = g_enemy[i].position.x;
			g_collisionEnemy.position.y = g_enemy[i].position.y;
		}
	}
}

void DrawEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].isUse) {
			spriteDraw(g_enemyTexture, g_enemy[i].position, D3DCOLOR_RGBA(255, 255, 255, 255));
		}
	}
}
void createEnemy(float x, float y)
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (!g_enemy[i].isUse)
		{
			g_enemy[i].position = { x,y,0.0f,1.0f };
			g_enemy[i].isUse = true;
			g_collisionEnemy.position.x = x;
			g_collisionEnemy.position.y = y;
			g_collisionEnemy.radius = 64; //enemysize * 0.5f
			break;
		}
	}
}

ENEMY *getEnemy()
{
	return g_enemy;
}

CIRCLE *getCollisionEnemy()
{
	return &g_collisionEnemy;
}