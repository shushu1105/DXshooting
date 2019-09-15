
#include "texture.h"
#include "sprite.h"
#include "font.h"
#include "player.h"

unsigned int fontTexture;
void SetFont(float x, float y, float width, float height, BULLET_ALPHA type);


void InitFont()
{
	fontTexture = TextureSetLoadFile("font.tga", 462, 258);

}

void UninitFont()
{

}

void UpdateFont()
{


}

void DrawFont()
{
	SetFont(120, 100, 60, 120, p);
	SetFont(90, 100, 60, 120, r);
	SetFont(30, 100, 60, 120, e);
	SetFont(130, 100, 60, 120, s);
	SetFont(190, 100, 60, 120, s);
	SetFont(220, 100, 60, 120, a);

	SetFont(930, 480, 60, 120, p);
	SetFont(870, 480, 60, 120, r);
	SetFont(810, 480, 60, 120, e);
	SetFont(750, 480, 60, 120, s);
	SetFont(690, 480, 60, 120, s);
	SetFont(660, 480, 60, 120, l);

	SetFont(930, 480, 60, 120, r);
	SetFont(870, 480, 60, 120, a);
	SetFont(810, 480, 60, 120, i);
	SetFont(750, 480, 60, 120, s);
	SetFont(690, 480, 60, 120, e);

	SetFont(630, 100, 60, 120, p);
	SetFont(690, 100, 60, 120, r);
	SetFont(750, 100, 60, 120, e);
	SetFont(810, 100, 60, 120, s);
	SetFont(870, 100, 60, 120, s);
	SetFont(930, 100, 60, 120, a);
}


void SetFont(float x, float y, float width, float height, BULLET_ALPHA type)
{
	spriteDivDraw(fontTexture, { x, y }, width, height,
		9, 3,			//(type % numX) * (1 / numX)
		type			//(type / numX) * (1 / numY)
	);
}
