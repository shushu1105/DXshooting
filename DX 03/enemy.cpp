

#include "enemy.h"
#include "texture.h"
#include "common.h"
#include "sprite.h"

ENEMY g_enemy[ENEMY_MAX];

int g_enemyTexture;
int g_flameCount;

void InitEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].isUse = false;
		g_enemy[i].move = { 1.0f,0.0f,0.0f,0.0f };
	}
	g_enemyTexture = TextureSetLoadFile("mark01.png", 64, 64);
}
void UninitEnemy()
{

}
void UpdateEnemy()
{
	switch (g_flameCount / 60 % 3)
	{
	case 0:
		createEnemy(500.0f, 500.0f);
		break;
	case 1:
		createEnemy(200.0f, 200.0f);
		break;
	case 2:
		createEnemy(400.0f, 100.0f);
	default:
		break;
	}
	g_flameCount++;
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
		if (g_enemy[i].isUse)continue;


		g_enemy[i].position = { x,y,0.0f,1.0f };
		g_enemy[i].isUse = true;
		return;
	}
}