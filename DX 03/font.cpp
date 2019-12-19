/************************************************
	
				font
					ゲーム用フォント処理

*************************************************/


#include "texture.h"
#include "sprite.h"
#include "font.h"
#include "player.h"

unsigned int fontTexture;
void SetFont(float x, float y, float width, float height, FONT_TYPE type);


void InitFont()
{
	fontTexture = TextureSetLoadFile("rom/texture/font.png");

}

void UninitFont()
{

}

void UpdateFont()
{


}

void DrawFont()
{

}


void SetFont(float x, float y, float width, float height, FONT_TYPE type)
{
	spriteDivDraw(
		fontTexture,
		{ x, y },
		width, height,
		9, 3,			//(type % numX) * (1 / numX)
		type,		//(type / numX) * (1 / numY)
		D3DCOLOR_RGBA(255, 255, 255, 255)
	);
}
