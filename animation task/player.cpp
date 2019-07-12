
#include "player.h"
#include "sprite.h"
#include "input.h"
#include "texture.h"
#include "common.h"
#include <math.h>

PLAYER g_player;
PLAYER g_runningMan[RUNNING_NUM];
static int g_cocoTexture;
static int g_runningTex[6];

int g_flame = 0;
int g_runningFlame = 0;

void positionResetRunning(Direction _direction);
void positionResetPlayer(Direction _direction);



void InitPlayer() {
	g_cocoTexture = TextureSetLoadFile("cocosozai.png", 512, 512);
	g_player.position = { SCREEN_WIDTH + SCREEN_WIDTH / 4 ,SCREEN_HEIGHT / 2,0.0f,1.0f };//{ 100.0f,100.0f,0.0f,1.0f };
	g_player.width = 64.0f;
	g_player.height = 64.0f;
	g_player.velocity = -1.0f;
	g_player.direction = LEFT;

	g_runningTex[0] = TextureSetLoadFile("runningman100L.png", 700, 400);
	g_runningTex[1] = TextureSetLoadFile("runningman101L.png", 700, 400);
	g_runningTex[2] = TextureSetLoadFile("runningman102L.png", 700, 400);
	g_runningTex[3] = TextureSetLoadFile("runningman100R.png", 700, 400);
	g_runningTex[4] = TextureSetLoadFile("runningman101R.png", 700, 400);
	g_runningTex[5] = TextureSetLoadFile("runningman102R.png", 700, 400);
	for (int i = 0; i < RUNNING_NUM; i++) {
		g_runningMan[i].position = { g_player.position.x + (float)(rand() % 200),g_player.position.y + (float)(rand() % 200 - 100),0.0f,1.0f };
		g_runningMan[i].width = rand() % 40 + 128.0f;
		g_runningMan[i].height = rand() % 40 + 128.0f;
		g_runningMan[i].velocity = -1.0f;
		g_runningMan[i].direction = LEFT;
	}
}
void UninitPlayer() {

}
void UpdatePlayer() {
	g_flame++;
	g_runningFlame++;

	g_player.position.x += MOVE * g_player.velocity;
	g_player.width++;
	g_player.height++;

	if (g_player.position.x >= (SCREEN_WIDTH / 2 + SCREEN_WIDTH))
	{
		positionResetPlayer(RIGHT);

	}

	if (g_player.position.x <= (SCREEN_WIDTH / 2 - SCREEN_WIDTH))
	{
		positionResetPlayer(LEFT);

	}

	if (g_runningFlame >= 100) {
		for (int i = 0; i < RUNNING_NUM; i++) {
			g_runningMan[i].position.x += (MOVE*1.2f) * g_runningMan[i].velocity;

			if (g_runningMan[i].position.x >= (SCREEN_WIDTH / 2 + SCREEN_WIDTH * 1.5f))
			{
				positionResetRunning(RIGHT);

			}

			if (g_runningMan[i].position.x <= (SCREEN_WIDTH / 2 - SCREEN_WIDTH * 1.5f))
			{
				positionResetRunning(LEFT);

			}
		}
	}
	g_player.position != g_player.position ? g_player.move = true : g_player.move = false;
}
void DrawPlayer() {


	if (g_player.direction == LEFT)
	{
		if (g_player.move) {
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
	}
	if (g_player.direction == RIGHT)
	{
		if (g_player.move) {
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
	}





	for (int i = 0; i < RUNNING_NUM; i++)
	{
		if (g_runningMan[i].direction == LEFT)
		{
			if (g_runningMan[i].move) {
				spriteDraw(g_runningTex[i % 3],
					g_runningMan[i].position,
					g_runningMan[i].width,
					g_runningMan[i].height,
					D3DCOLOR_RGBA(255, 255, 255, 255),
					700, 0, -140, -200);
			}
			else {
				spriteDrawDivAnim(
					g_runningTex[i % 3],
					g_runningMan[i].position,
					g_runningMan[i].width,
					g_runningMan[i].height,
					D3DCOLOR_RGBA(255, 255, 255, 255),
					5, 2, 5 * 2,
					SPEED,
					0, 10);
			}
		}
		if (g_runningMan[i].direction == RIGHT)
		{
			if (g_runningMan[i].move) {
				spriteDraw(g_runningTex[i % 3 + 3],
					g_runningMan[i].position,
					g_runningMan[i].width,
					g_runningMan[i].height,
					D3DCOLOR_RGBA(255, 255, 255, 255),
					700, 0, -140, -200);
			}
			else {
				spriteDrawDivAnim(
					g_runningTex[i % 3 + 3],
					g_runningMan[i].position,
					g_runningMan[i].width,
					g_runningMan[i].height,
					D3DCOLOR_RGBA(255, 255, 255, 255),
					5, 2, 5 * 2,
					SPEED,
					0, 10);
			}
		}
	}





}

PLAYER *GetPlayer()
{
	return &g_player;
}

int GetFlame()
{
	return g_flame;
}

void positionResetPlayer(Direction _direction)
{
	g_player.velocity *= -1;
	g_player.width = 64.0f;
	g_player.height = 64.0f;

	if (_direction == RIGHT)
	{
		g_player.position.x = (SCREEN_WIDTH / 2 + SCREEN_WIDTH);
		g_player.position.y = SCREEN_HEIGHT * 1 / 4;
		g_player.direction = LEFT;

	}
	else  if (_direction == LEFT) {
		g_player.position.x = (SCREEN_WIDTH / 2 - SCREEN_WIDTH);
		g_player.position.y = SCREEN_HEIGHT * 3 / 4;
		g_player.direction = RIGHT;
	}

}


void positionResetRunning(Direction _direction)
{
	if (_direction == RIGHT)
	{
		for (int i = 0; i < RUNNING_NUM; i++) {
			g_runningMan[i].position.x = (SCREEN_WIDTH / 2 + SCREEN_WIDTH) + (float)(rand() % 200);
			g_runningMan[i].position.y = (SCREEN_HEIGHT * 1 / 4) + (float)(rand() % 200 - 100);
			g_runningMan[i].direction = LEFT;
			g_runningMan[i].velocity *= -1;
			g_runningFlame = 0;
		}
	}
	else if (_direction == LEFT) {
		for (int i = 0; i < RUNNING_NUM; i++)
		{
			g_runningMan[i].position.x = (SCREEN_WIDTH / 2 - SCREEN_WIDTH) - (float)(rand() % 200);
			g_runningMan[i].position.y = (SCREEN_HEIGHT * 3 / 4) + (float)(rand() % 200 - 100);
			g_runningMan[i].direction = RIGHT;
			g_runningMan[i].velocity *= -1;
			g_runningFlame = 0;
		}
	}

}
