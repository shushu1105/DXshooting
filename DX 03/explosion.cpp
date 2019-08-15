
#include "explosion.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"

EXPLOSION g_explosion;
unsigned int g_explosionTex;

void InitExplosion()
{
	g_explosionTex = TextureSetLoadFile("explosion.png", 480, 288);
}
void UninitExplosion()
{

}
void UpdateExplosion()
{
	if (g_explosion.isUse)
		g_explosion.flameCount++;
}
void DrawExplosion()
{
	if (g_explosion.isUse) {
		spriteDrawDivAnim(
			g_explosionTex,
			g_explosion.position,
			128, 128,
			D3DCOLOR_RGBA(255, 255, 255, 255),
			5, 3, 15,
			5,
			0, 14,
			g_explosion.flameCount
		);
	}
	if (g_explosion.flameCount >= (5 * 15 - 1))
	{
		g_explosion.isUse = false;
		g_explosion.flameCount = 0;
	}
}

void SetExplosion(D3DXVECTOR2 _explosionPosition)
{
	g_explosion.position.x = _explosionPosition.x;
	g_explosion.position.y = _explosionPosition.y;
	g_explosion.position.z = 0.0f;
	g_explosion.position.w = 1.0f;
	g_explosion.flameCount = 0;
	g_explosion.isUse = true;
}