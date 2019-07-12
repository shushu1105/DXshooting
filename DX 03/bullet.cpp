
#include "bullet.h"
#include "texture.h"
#include "common.h"
#include "sprite.h"

BULLET g_bullet[BULLET_MAX];

int g_bulletTexture;

void InitBullet()
{
	for (int i = 0; i < BULLET_MAX; i++) {
		g_bullet[i].isUse = false;
		g_bullet[i].move = { 1.0f,0.0f,0.0f,0.0f };
	}
	g_bulletTexture = TextureSetLoadFile("bullet.png", 512, 256);
}
void UninitBullet()
{

}
void UpdateBullet()
{
	for (int i = 0; i < BULLET_MAX; i++) {
		if (g_bullet[i].isUse) {
			if (g_bullet[i].direction == LEFT)
				g_bullet[i].position -= g_bullet[i].move;

			if (g_bullet[i].direction == RIGHT)
				g_bullet[i].position += g_bullet[i].move;

			g_bullet[i].flameCount++;
			if (g_bullet[i].flameCount >= 300) {
				g_bullet[i].isUse = false;
				g_bullet[i].flameCount = 0;
			}
		}
	}
}

void DrawBullet()
{
	for (int i = 0; i < BULLET_MAX; i++) {
		if (g_bullet[i].isUse) {
			spriteDrawDivAnim(
				g_bulletTexture,
				g_bullet[i].position,
				32, 32,
				D3DCOLOR_RGBA(255, 255, 255, 255),
				16, 8, 16 * 8,
				4,
				0, 13
			);
		}
	}
}
void createBullet(float x, float y, Direction direction)
{
	for (int i = 0; i < BULLET_MAX; i++) {
		if (g_bullet[i].isUse)
			continue;
		g_bullet[i].direction = direction;
		g_bullet[i].position = { x,y,0.0f,1.0f };
		g_bullet[i].isUse = true;
		g_bullet[i].flameCount = 0;
		return;
	}
}