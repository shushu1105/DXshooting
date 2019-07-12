
#include "explosion.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"
#include "player.h"

EXPLOSION g_explosion;
unsigned int g_explosionTex;

void InitExplosion()
{
	g_explosionTex = TextureSetLoadFile("explosion.png", 250, 250);
}
void UninitExplosion()
{

}
void UpdateExplosion()
{

}
void DrawExplosion()
{
	spriteDrawDivAnim(
		g_explosionTex,
		g_explosion.position,
		32, 32,
		D3DCOLOR_RGBA(255, 255, 255, 255),
		8, 8, 60,
		1,
		0, 60
	);
}