
#include "player.h"
#include "sprite.h"
#include "input.h"
#include "texture.h"
#include "common.h"
#include <math.h>

PLAYER g_player;
static int g_cocoTexture;
int angle = 0;
float fsin[360], fcos[360];
bool statusWait();


void InitPlayer() {
	g_cocoTexture = TextureSetLoadFile("cocosozai.png", 512, 512);
	g_player.position = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f,1.0f };//{ 100.0f,100.0f,0.0f,1.0f };
	g_player.width = 128.0f;
	g_player.height = 128.0f;
	g_player.velocity = 0.9f;
	g_player.direction = RIGHT;
	for (int i = 0; i < 360; i++) {
		fsin[i] = (float)sin(D3DXToRadian(i));
		fcos[i] = (float)cos(D3DXToRadian(i));
	}
}
void UninitPlayer() {

}
void UpdatePlayer() {
	g_player.move.x *= g_player.velocity;
	g_player.move.y *= g_player.velocity;
	angle = -1;
	//[38]ª [40]«   [37]©   [39]¨

	if (Keyboard_IsPress(DIK_RIGHT) && Keyboard_IsPress(DIK_UP))    //‰Eã
	{
		angle = 315;
		g_player.direction = RIGHT;
	}
	else if (Keyboard_IsPress(DIK_LEFT) && Keyboard_IsPress(DIK_UP))    //¶ã
	{
		angle = 225;
		g_player.direction = LEFT;
	}
	else if (Keyboard_IsPress(DIK_LEFT) && Keyboard_IsPress(DIK_DOWN))    //¶‰º
	{
		angle = 135;
		g_player.direction = LEFT;

	}
	else if (Keyboard_IsPress(DIK_RIGHT) && Keyboard_IsPress(DIK_DOWN))    //‰E‰º
	{
		angle = 45;
		g_player.direction = RIGHT;

	}
	else if (Keyboard_IsPress(DIK_UP))    //ª
	{
		angle = 270;
		g_player.direction = UP;
		g_player.width -= 2.0;
		g_player.height -= 2.0f;
	}
	else if (Keyboard_IsPress(DIK_DOWN))    //«
	{
		angle = 90;
		g_player.direction = DOWN;
		g_player.width += 2.0f;
		g_player.height += 2.0f;
	}
	else if (Keyboard_IsPress(DIK_LEFT))    //©
	{
		angle = 180;
		g_player.direction = LEFT;
	}
	else if (Keyboard_IsPress(DIK_RIGHT))    //¨
	{
		angle = 0;
		g_player.direction = RIGHT;
	}

	if (angle != -1) {
		g_player.move.x += fcos[angle] * g_player.velocity;
		g_player.move.y += fsin[angle] * g_player.velocity;
	}



	g_player.position += g_player.move;
}
void DrawPlayer() {
	switch (g_player.direction)
	{
	case LEFT:
		if (statusWait()) {
			spriteDraw(g_cocoTexture,
				g_player.position,
				g_player.width,
				g_player.height,
				D3DCOLOR_RGBA(255, 255, 255, 255),
				0, 32, 32, 32);
		}
		else {
			spriteDrawDivAnim(
				g_cocoTexture,
				g_player.position,
				g_player.width,
				g_player.height,
				D3DCOLOR_RGBA(255, 255, 255, 255),
				16, 16, 16 * 16,
				SPEED,
				16, 28);
		}
		break;
	case RIGHT:
		if (statusWait()) {
			spriteDraw(g_cocoTexture,
				g_player.position,
				g_player.width,
				g_player.height,
				D3DCOLOR_RGBA(255, 255, 255, 255),
				0, 0, 32, 32);
		}
		else {
			spriteDrawDivAnim(
				g_cocoTexture,
				g_player.position,
				g_player.width,
				g_player.height,
				D3DCOLOR_RGBA(255, 255, 255, 255),
				16, 16, 16 * 16,
				SPEED,
				0, 12);
		}
		break;
	case UP:
		if (statusWait()) {
			spriteDraw(g_cocoTexture,
				g_player.position,
				g_player.width,
				g_player.height,
				D3DCOLOR_RGBA(255, 255, 255, 255),
				0, 0, 32, 32);
		}
		else {
			spriteDrawDivAnim(
				g_cocoTexture,
				g_player.position,
				g_player.width,
				g_player.height,
				D3DCOLOR_RGBA(255, 255, 255, 255),
				16, 16, 16 * 16,
				SPEED,
				32, 37
			);
		}
		break;
	case DOWN:
		if (statusWait()) {
			spriteDraw(g_cocoTexture,
				g_player.position,
				g_player.width,
				g_player.height,
				D3DCOLOR_RGBA(255, 255, 255, 255),
				0, 0, 32, 32);
		}
		else {
			spriteDrawDivAnim(
				g_cocoTexture,
				g_player.position,
				g_player.width,
				g_player.height,
				D3DCOLOR_RGBA(255, 255, 255, 255),
				16, 16, 16 * 16,
				SPEED,
				48, 55
			);
		}
		break;
	default:
		break;
	}
}

PLAYER *GetPlayer() {
	return &g_player;
}

bool statusWait() {
	if (fabsf(g_player.move.x) < 0.1f && fabs(g_player.move.y) < 0.1f) {
		g_player.move = { 0.0f,0.0f,0.0f,1.0f };
		return true;
	}
	return false;
}