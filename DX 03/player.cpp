
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
#include "frameCounter.h"
#include "sound.h"

PLAYER g_player;
float fsin[360], fcos[360];
bool statusWait();
int isMoveAngle();

void InitPlayer()
{
	g_player.texture = TextureSetLoadFile("rom/texture/character.png");
	g_player.position = { SCREEN_WIDTH / 2,SCREEN_HEIGHT * 3 / 4 };
	g_player.width = 48.0f;
	g_player.height = 48.0f;
	g_player.velocity = 0.9f;
	g_player.hp = 5;
	g_player.damageTime = 0;

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
	if (g_player.damageTime > 0)
	{
		g_player.damageTime--;
	}
	if (!isDead())
	{

		g_player.move.x *= g_player.velocity;
		g_player.move.y *= g_player.velocity;

		if (GetSearchGamePad() == 0)
		{
			if (isMoveAngle() != -1)
			{
				g_player.move.x += fcos[isMoveAngle()] * g_player.velocity;
				g_player.move.y += fsin[isMoveAngle()] * g_player.velocity;
			}
		}
		else
		{
			if (GamePad_IsPress(0, BUTTON_UP))
				g_player.move.y -= g_player.velocity;
			if (GamePad_IsPress(0, BUTTON_DOWN))
				g_player.move.y += g_player.velocity;
			if (GamePad_IsPress(0, BUTTON_LEFT))
				g_player.move.x -= g_player.velocity;
			if (GamePad_IsPress(0, BUTTON_RIGHT))
				g_player.move.x += g_player.velocity;

		}

		if (statusWait()) g_player.move = { 0.0f,0.0f };


		if (Keyboard_IsTrigger(DIK_SPACE) ||
			GamePad_IsTrigger(0, BUTTON_CIRCLE) ||
			GamePad_IsTrigger(0, BUTTON_CROSS) ||
			GamePad_IsTrigger(0, BUTTON_TRIANGLE) ||
			GamePad_IsTrigger(0, BUTTON_SQUARE))
		{
			createBullet(g_player.position.x, g_player.position.y - 5.0f);
			PlaySound(SOUND_LABEL_SHOT);
		}
		//wrap(g_player.position.x, 0.0f, SCREEN_WIDTH);
		clamp(g_player.position.x, g_player.width, 0.0f + g_player.width*0.5f, SCREEN_WIDTH - g_player.width*0.5f);
		clamp(g_player.position.y, g_player.height, 0.0f + g_player.height*0.5f, SCREEN_HEIGHT - g_player.height*0.5f);



		g_player.position.move(g_player.move.x, g_player.move.y);
		g_player.collision.Update(g_player.position);
	}
}


void DrawPlayer()
{
	if (g_player.damageTime % 5 == 0)
	{
		spriteDrawDivAnim(
			g_player.texture,
			{ g_player.position.x,g_player.position.y },
			g_player.width,
			g_player.height,
			12, 8, 12 * 8,
			SPEED,
			36, 38,
			g_player.damageTime != 0 ? D3DCOLOR_RGBA(255, 0, 0, 255) : D3DCOLOR_RGBA(255, 255, 255, 255)
		);
	}
}


int isMoveAngle()
{
	//âEè„
	if (Keyboard_IsPress(DIK_RIGHT) && Keyboard_IsPress(DIK_UP))
		return	315;
	//ç∂è„
	if (Keyboard_IsPress(DIK_LEFT) && Keyboard_IsPress(DIK_UP))
		return  225;
	//ç∂â∫
	if (Keyboard_IsPress(DIK_LEFT) && Keyboard_IsPress(DIK_DOWN))

		return 135;
	//âEâ∫
	if (Keyboard_IsPress(DIK_RIGHT) && Keyboard_IsPress(DIK_DOWN))
		return  45;

	//Å™
	if (Keyboard_IsPress(DIK_UP))
		return  270;
	//Å´
	if (Keyboard_IsPress(DIK_DOWN))
		return  90;
	//Å©
	if (Keyboard_IsPress(DIK_LEFT))
		return  180;

	//Å®
	if (Keyboard_IsPress(DIK_RIGHT))
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

void Damage(int damage)
{
	g_player.hp -= damage;
	g_player.damageTime = 120;
	PlaySound(SOUND_LABEL_DAMAGE);
}

bool isDead()
{
	return g_player.hp <= 0 ? true : false;
}

bool NoneStatus()
{
	return g_player.damageTime == 0 ? true : false;
}