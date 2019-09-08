
#include "score.h"
#include "common.h"
#include "texture.h"
#include "sprite.h"
#include "Fujino.h"
#include"debug_font.h"

#define SPEED (60)

Score g_score;
Score g_goalScore;

static int g_flameCounter;

static void numberDraw(int _n, D3DXVECTOR2 _position);

static int deference(int a, int b);
static int incrementSpeed();

void InitScore()
{
	g_score.num = 0;
	g_score.position = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
	g_score.width = 50.0f;
	g_score.height = 50.0f;
	g_score.texture = TextureSetLoadFile("number.tga", 320, 32);
}

void UninitScore()
{
	g_score.num = NULL;
	g_score.position = { NULL,NULL };
	g_score.width = NULL;
	g_score.height = NULL;
}

void UpdateScore()
{

	g_score.num += incrementSpeed();

	clamp(g_score.num, 0, g_goalScore.num);
	
}


void DrawScore()
{

	numberDraw(
		g_score.num,
		g_score.position
	);
}

static void numberDraw(int _n, D3DXVECTOR2 _position)
{
	for (int i = 0; i < TRUSS; i++)
	{
		spriteDivDraw(
			g_score.texture,
			{ _position.x - g_score.width*i,_position.y},
			g_score.width,
			g_score.height,
			10, 1,
			_n % 10
		);
		_n /= 10;
	}
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
		if (deference(g_goalScore.num, g_score.num) < pow(10, i))return 10 * i;

	return 0;
}