
#include "bg.h"
#include "texture.h"
#include "sprite.h"
#include "common.h"

static int BGTexture = 0;

void InitBG()
{
	BGTexture = TextureSetLoadFile("BG.png", SCREEN_WIDTH, SCREEN_HEIGHT);
}

void UninitBG()
{

}

void UpdateBG()
{

}

void DrawBG()
{
	spriteDraw(
		BGTexture,
		{ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 });
}