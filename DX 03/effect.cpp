
#include "texture.h"
#include "effect.h"
#include "frameCounter.h"
#include "sprite.h"
#include "spriteAnim.h"
#include "direct3d.h"

#define EFFECT_MAX (256)

typedef struct
{
	Vector2 position;
	float scale;
	D3DCOLOR color;
	float life;
	int birthFlame;
}Effect;

Effect g_effect[EFFECT_MAX];
unsigned int effectTexture;

bool isUsedEffect(int id);

void InitEffect()
{
	effectTexture = TextureSetLoadFile("effect000.jpg", 80, 80);
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		g_effect[i].life = 0;
	}
}

void UninitEffect()
{

}
void UpdateEffect()
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!isUsedEffect(i))
			continue;

		int age = GetFlameCounter() - g_effect[i].birthFlame;

		if (g_effect[i].life <= age)
		{
			g_effect[i].life = 0;
			continue;
		}
		float e = (float)age / g_effect[i].life;
		D3DXCOLOR color = g_effect[i].color;
		color.a = 1 - e;
		g_effect[i].color = color;
		g_effect[i].scale *= (1 - (e * 1 / 10));
	}
}
void DrawEffect()
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	SetRender(pDevice, RENDER_ADDBLEND);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!isUsedEffect(i))
			continue;

		SetSpriteColor(g_effect[i].color);
		spriteDraw(
			effectTexture,
			{ g_effect[i].position.x,g_effect[i].position.y },
			g_effect[i].scale,
			g_effect[i].scale
		);
	}
	SetRender(pDevice, RENDER_NORMALBLEND);
	SetSpriteColor(D3DCOLOR_RGBA(255, 255, 255, 255));
}


void createEffect(float x, float y, D3DCOLOR color, int life, float scale)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (isUsedEffect(i))
			continue;

		g_effect[i].position.x = x;
		g_effect[i].position.y = y;
		g_effect[i].color = color;
		g_effect[i].life = life;
		g_effect[i].birthFlame = GetFlameCounter();
		g_effect[i].scale = scale;
		break;
	}
}

bool isUsedEffect(int id)
{
	return g_effect[id].life > 0 ? true : false;
}