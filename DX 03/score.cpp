/*********************************************

			score
					ゲーム用スコア表示

**********************************************/
#include "score.h"
#include "common.h"
#include "texture.h"
#include "sprite.h"
#include "Fujino.h"
#include"debug_font.h"
#include "player.h"
#include "scene.h"

Score g_score;
Score g_goalScore;
Pop g_pop[POP_MAX];

static int g_flameCounter;
unsigned int g_ScoreTexture;

static void hpDraw(int hp, D3DXVECTOR2 _position);
static void popDraw(int id);

static int deference(int a, int b);
static int incrementSpeed();

void InitScore()
{
	g_ScoreTexture = TextureSetLoadFile("rom/texture/number.png");
	if (GetScene() == SCENE_GAME)
	{
		g_score.position = { SCREEN_WIDTH - 50.0f,30.0f };
		g_score.width = 50.0f;
		g_score.height = 50.0f;
		g_score.num = 0;
		g_goalScore.num = 0;

		for (int i = 0; i < POP_MAX; i++)
		{
			g_pop[i].position = { 0.0f,0.0f };
			g_pop[i].width = 32.0f;
			g_pop[i].height = 32.0f;
			g_pop[i].num = 0;
			g_pop[i].isUse = false;
		}
	}
}

void UninitScore()
{

}

void UpdateScore()
{

	g_score.num += incrementSpeed();
	clamp(g_goalScore.num, 0, 999999999);
	clamp(g_score.num, 0, g_goalScore.num);

	if (GetScene() == SCENE_RESULT)
		g_score.num = g_goalScore.num;

	for (int i = 0; i < POP_MAX; i++)
	{
		if (g_pop[i].isUse)
		{
			g_pop[i].position.y--;
			g_pop[i].frame++;
			if (g_pop[i].frame >= SecondsToFrame(1))
				DeletePop(i);
		}
	}

}


void DrawScore()
{
	static PLAYER *pPlayer = getPlayer();

	numberDraw(
		g_score.num,
		g_score.position,
		g_score.width,
		g_score.height
	);

	hpDraw(
		pPlayer->hp,
		{ 50.0f,30.0f }
	);

	for (int i = 0; i < POP_MAX; i++)
	{
		if (g_pop[i].isUse)
			popDraw(i);
	}

}

void numberDraw(int _n, D3DXVECTOR2 _position, float width, float height)
{
	for (int i = 0; i < TRUSS; i++)
	{
		spriteDivDraw(
			g_ScoreTexture,
			{ _position.x - width * i,_position.y },
			width,
			height,
			5, 5,
			_n % 10,
			D3DCOLOR_RGBA(200, 255, 200, 255)
		);
		_n /= 10;
		if (_n == 0)break;
	}
}

static void hpDraw(int hp, D3DXVECTOR2 _position)
{
	for (int i = 0; i < hp; i++)
	{
		spriteDivDraw(
			g_ScoreTexture,
			{ _position.x + 50.0f*i,_position.y },
			50.0f,
			50.0f,
			5, 5,
			10,
			D3DCOLOR_RGBA(255, 0, 0, 255)
		);
	}
}

static void popDraw(int id)
{
	spriteDivDraw(
		g_ScoreTexture,
		{ g_pop[id].position.x,g_pop[id].position.y },
		g_pop[id].width,
		g_pop[id].height,
		5, 5,
		g_pop[id].num,
		D3DCOLOR_RGBA(255, 50, 50, 255)
	);
}


void AddScore(int _n)
{
	g_goalScore.num += _n;
}

static int deference(int a, int b)
{
	return a - b;
}

static int incrementSpeed()
{
	for (int i = 0; i < TRUSS; i++)
		if (deference(g_goalScore.num, g_score.num) < pow(10, i))return i * i;

	return 0;
}

void SetPop(float x, float y, int num)
{
	int digit = digitCount(num);
	int localNum = num;

	for (int i = 0; i < POP_MAX; i++)
	{
		if (g_pop[i].isUse)
			continue;

		for (int j = 0; j < digit; j++)
		{

			if (digit == 1)
			{
				g_pop[i + j].position.x = x;
			}
			else if (digit % 2 == 0)
			{
				g_pop[i + j].position.x = x - g_pop[i + j].width *j + g_pop[i + j].width *0.5f*(digit - 1);
			}
			else if (digit % 2 == 1)
			{
				g_pop[i + j].position.x = x - g_pop[i + j].width *j + g_pop[i + j].width *(digit - 2);
			}

			g_pop[i + j].position.y = y;
			g_pop[i + j].num = localNum % 10;
			g_pop[i + j].frame = 0;
			g_pop[i + j].isUse = true;

			localNum /= 10;
		}
		break;
	}
}

void DeletePop(int id)
{
	if (g_pop[id].isUse)
	{
		g_pop[id].isUse = false;
		g_pop[id].num = 0;
	}
}

int GetScore()
{
	return g_score.num;
}