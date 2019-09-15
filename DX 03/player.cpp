
#include "player.h"
#include "sprite.h"
#include "input.h"
#include "texture.h"
#include "common.h"
#include <math.h>
#include "bullet.h"
#include "sound.h"
#include "score.h"
#include "effect.h"


PLAYER g_player;
int angle = 0;
float fsin[360], fcos[360];
bool statusWait();
int isMoveAngle();
bool pressAnyAlpha();
BULLET_ALPHA shotType();
static int g_FrameCounter = 0;

void InitPlayer()
{
	g_player.texture = TextureSetLoadFile("character.png", 576, 384);
	g_player.position = { SCREEN_WIDTH / 2,SCREEN_HEIGHT * 3 / 4 };
	g_player.width = 32.0f;
	g_player.height = 32.0f;
	g_player.velocity = 0.9f;

	for (int i = 0; i < 360; i++) {
		fsin[i] = (float)sin(D3DXToRadian(i));
		fcos[i] = (float)cos(D3DXToRadian(i));
	}
}


void UninitPlayer()
{

}


void UpdatePlayer()
{
	g_player.move.x *= g_player.velocity;
	g_player.move.y *= g_player.velocity;



	if (isMoveAngle() != -1)
	{
		g_player.move.x += fcos[isMoveAngle()] * g_player.velocity;
		g_player.move.y += fsin[isMoveAngle()] * g_player.velocity;
		AddScore(25);
	}


	if (statusWait()) g_player.move = { 0.0f,0.0f };
	else
	{
		createEffect(g_player.position.x, g_player.position.y, D3DCOLOR_RGBA(200, 50, 100, 192), 20, g_player.width);

	}
	if (pressAnyAlpha()) createBullet(g_player.position.x, g_player.position.y - 5.0f, BULLETSIZE, shotType());


	wrap(g_player.position.x, 0.0f, SCREEN_WIDTH);
	//clamp(g_player.position.x, g_player.width, 0, SCREEN_WIDTH);
	clamp(g_player.position.y, g_player.height, 0.0f, SCREEN_HEIGHT);


	g_player.position.x += g_player.move.x;
	g_player.position.y += g_player.move.y;
	g_FrameCounter++;


	g_player.collision.Update(g_player.position);

}


void DrawPlayer()
{	spriteDrawDivAnim(
		g_player.texture,
		{ g_player.position.x,g_player.position.y },
		g_player.width,
		g_player.height,
		12, 8, 12 * 8,
		SPEED,
		37, 37);

}


int isMoveAngle()
{
	if (Keyboard_IsPress(DIK_RIGHT) && Keyboard_IsPress(DIK_UP))    //‰Eã
		return	315;

	if (Keyboard_IsPress(DIK_LEFT) && Keyboard_IsPress(DIK_UP))    //¶ã
		return  225;

	if (Keyboard_IsPress(DIK_LEFT) && Keyboard_IsPress(DIK_DOWN))    //¶‰º
		return 135;

	if (Keyboard_IsPress(DIK_RIGHT) && Keyboard_IsPress(DIK_DOWN))    //‰E‰º
		return  45;

	if (Keyboard_IsPress(DIK_UP))    //ª
		return  270;

	if (Keyboard_IsPress(DIK_DOWN))    //«
		return  90;

	if (Keyboard_IsPress(DIK_LEFT))    //©
		return  180;

	if (Keyboard_IsPress(DIK_RIGHT))    //¨
		return 0;

	return -1;
}


PLAYER *getPlayer()
{
	return &g_player;
}

bool statusWait()
{
	if (fabs(g_player.move.x) < 0.5f && fabs(g_player.move.y) < 0.1f) {
		return true;
	}
	return false;
}

bool pressAnyAlpha()
{
	if (Keyboard_IsTrigger(DIK_A) ||
		Keyboard_IsTrigger(DIK_B) ||
		Keyboard_IsTrigger(DIK_C) ||
		Keyboard_IsTrigger(DIK_D) ||
		Keyboard_IsTrigger(DIK_E) ||
		Keyboard_IsTrigger(DIK_F) ||
		Keyboard_IsTrigger(DIK_G) ||
		Keyboard_IsTrigger(DIK_H) ||
		Keyboard_IsTrigger(DIK_I) ||
		Keyboard_IsTrigger(DIK_J) ||
		Keyboard_IsTrigger(DIK_K) ||
		Keyboard_IsTrigger(DIK_L) ||
		Keyboard_IsTrigger(DIK_M) ||
		Keyboard_IsTrigger(DIK_N) ||
		Keyboard_IsTrigger(DIK_O) ||
		Keyboard_IsTrigger(DIK_P) ||
		Keyboard_IsTrigger(DIK_Q) ||
		Keyboard_IsTrigger(DIK_R) ||
		Keyboard_IsTrigger(DIK_S) ||
		Keyboard_IsTrigger(DIK_T) ||
		Keyboard_IsTrigger(DIK_U) ||
		Keyboard_IsTrigger(DIK_V) ||
		Keyboard_IsTrigger(DIK_W) ||
		Keyboard_IsTrigger(DIK_X) ||
		Keyboard_IsTrigger(DIK_Y) ||
		Keyboard_IsTrigger(DIK_Z))
		return true;

	return false;
}

BULLET_ALPHA shotType()
{
	if (Keyboard_IsTrigger(DIK_A))return a;
	if (Keyboard_IsTrigger(DIK_B))return b;
	if (Keyboard_IsTrigger(DIK_C))return c;
	if (Keyboard_IsTrigger(DIK_D))return d;
	if (Keyboard_IsTrigger(DIK_E))return e;
	if (Keyboard_IsTrigger(DIK_F))return f;
	if (Keyboard_IsTrigger(DIK_G))return g;
	if (Keyboard_IsTrigger(DIK_H))return h;
	if (Keyboard_IsTrigger(DIK_I))return i;
	if (Keyboard_IsTrigger(DIK_J))return j;
	if (Keyboard_IsTrigger(DIK_K))return k;
	if (Keyboard_IsTrigger(DIK_L))return l;
	if (Keyboard_IsTrigger(DIK_M))return m;
	if (Keyboard_IsTrigger(DIK_N))return n;
	if (Keyboard_IsTrigger(DIK_O))return o;
	if (Keyboard_IsTrigger(DIK_P))return p;
	if (Keyboard_IsTrigger(DIK_Q))return q;
	if (Keyboard_IsTrigger(DIK_R))return r;
	if (Keyboard_IsTrigger(DIK_S))return s;
	if (Keyboard_IsTrigger(DIK_T))return t;
	if (Keyboard_IsTrigger(DIK_U))return u;
	if (Keyboard_IsTrigger(DIK_V))return v;
	if (Keyboard_IsTrigger(DIK_W))return w;
	if (Keyboard_IsTrigger(DIK_X))return x;
	if (Keyboard_IsTrigger(DIK_Y))return y;
	if (Keyboard_IsTrigger(DIK_Z))return z;

	return ALPHA_MAX;
}